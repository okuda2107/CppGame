#include "renderer/Renderer.h"

#include <algorithm>

#include "GL/glew.h"
// #include "UI/UIScreen.h"
#include "UI/Font.h"
#include "core/Game.h"
#include "object/Actor.h"
#include "renderer/Mesh.h"
#include "renderer/MeshComponent.h"
#include "renderer/Shader.h"
#include "renderer/SkydomeComponent.h"
#include "renderer/SpriteComponent.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"

Renderer::Renderer(UISystem* system)
    : mContext(nullptr),
      mScreenHeight(0.0f),
      mScreenWidth(0.0f),
      mSkydome(nullptr),
      mSpriteVerts(nullptr),
      mSpriteShader(nullptr),
      mWindow(nullptr),
      mUISystem(system) {}

Renderer::~Renderer() {}

bool Renderer::Initialize(float screenWidth, float screenHeight) {
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // depthバッファの指定 各ピクセルの奥行きの情報
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // ダブルバッファリング有効
    // 裏に描画され，swapで描画しきった画面を入れ替える
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    mWindow = SDL_CreateWindow(
        "Game Programming in C++", 100, 100, static_cast<int>(mScreenWidth),
        static_cast<int>(mScreenHeight),
        SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!mWindow) {
        SDL_Log("Faled to Create Window:%s", SDL_GetError());
        return false;
    }

    // OpenGLのコンテキスト (リソースの管理や実行を行う環境) の作成
    mContext = SDL_GL_CreateContext(mWindow);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_Log("Failed to Initialize GLEW");
        return false;
    }
    glGetError();

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        SDL_Log("Failed to initialize SDL_ttf");
        return false;
    }

    if (!LoadShaders()) {
        SDL_Log("Failed to Load Shaders");
        return false;
    }

    CreateSpriteVerts();

    return true;
}

void Renderer::Shutdown() {
    delete mSpriteVerts;
    mSpriteShader->Unload();
    delete mSpriteShader;
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData() {
    // Destroy textures
    for (auto i : mTextures) {
        i.second->Unload();
        delete i.second;
    }
    mTextures.clear();

    // Destroy meshes
    for (auto i : mMeshes) {
        i.second->Unload();
        delete i.second;
    }
    mMeshes.clear();

    // Destroy shaders
    for (auto i : mShaders) {
        i.second->Unload();
        delete i.second;
    }
    mShaders.clear();
}

void Renderer::Draw() {
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 背景描画
    // todo: 複数の背景オブジェクトに対応？
    if (mSkydome != nullptr) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);  // 深度書き込み禁止

        // 背景用のビュー行列 (平行移動成分を除去)
        Matrix4 viewNoTrans = mView;
        viewNoTrans.mat[3][0] = 0.0f;  // x平行移動消去
        viewNoTrans.mat[3][1] = 0.0f;  // y平行移動消去
        viewNoTrans.mat[3][2] = 0.0f;  // z平行移動消去

        Matrix4 viewProj = viewNoTrans * mProjection;
        mSkydome->Draw(viewProj);

        glDepthMask(GL_TRUE);
        glDisable(GL_CULL_FACE);
    }

    // メッシュ描画
    for (auto mc : mMeshComps) {
        ApplyConfig(mc.first);

        for (auto shader : mShaders) {
            shader.second->SetActive();
            shader.second->SetMatrixUniform("uViewProj", mView * mProjection);
            SetLightUniforms(shader.second);
            for (auto mc : mc.second) {
                mc->Draw(shader.first, shader.second);
            }
        }

        ResetConfig();
    }

    // スプライト描画
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // Set shader/vao as active
    mSpriteShader->SetActive();
    mSpriteVerts->SetActive();
    for (auto sprite : mSprites) {
        sprite->Draw(mSpriteShader);
    }

    // Draw UI
    // for (auto ui : mGame->GetUIStack()) {
    //     ui->Draw(mSpriteShader);
    // }

    SDL_GL_SwapWindow(mWindow);
}

void Renderer::ApplyConfig(const ConfigID id) {
    RenderConfig config = mMeshConfigs.at(id);
    if (config.mBlend)
        glEnable(GL_BLEND);
    else if (!config.mBlend)
        glDisable(GL_BLEND);

    if (config.mCullFaceBack) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    if (config.mDepthMask)
        glDepthMask(GL_TRUE);
    else if (!config.mDepthMask)
        glDepthMask(GL_FALSE);

    if (config.mDepthTest)
        glEnable(GL_DEPTH_TEST);
    else if (!config.mDepthTest)
        glDisable(GL_DEPTH_TEST);

    // カメラから遠い順に描画
    if (config.mSortByCamera) {
        auto comps = mMeshComps.at(id);
        Matrix4 invView = mView;
        invView.Invert();
        Vector3 cameraPos = invView.GetTranslation();
        // 半透明相当の描画設定 → 遠い順にソート
        std::sort(comps.begin(), comps.end(),
                  [cameraPos](MeshComponent* a, MeshComponent* b) {
                      float distA =
                          (a->GetOwner()->GetPosition() - cameraPos).LengthSq();
                      float distB =
                          (b->GetOwner()->GetPosition() - cameraPos).LengthSq();
                      return distA > distB;  // 遠い順
                  });
    }
}

void Renderer::ResetConfig() {
    // todo: 状態をリセットすることを検討
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
}

void Renderer::AddSprite(class SpriteComponent* sprite) {
    auto iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter) {
        if ((*iter)->GetDrawOrder() > sprite->GetDrawOrder()) {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(class SpriteComponent* sprite) {
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Renderer::AddMeshComp(const ConfigID id, MeshComponent* mesh) {
    auto iter = mMeshComps.find(id);
    if (iter != mMeshComps.end()) {
        iter->second.push_back(mesh);
    } else {
        mMeshComps.emplace(id, std::vector<MeshComponent*>{mesh});
    }
}

void Renderer::RemoveMeshComp(const ConfigID id, MeshComponent* mesh) {
    auto vectorIter = mMeshComps.find(id);
    if (vectorIter != mMeshComps.end()) {
        auto meshIter = std::find(vectorIter->second.begin(),
                                  vectorIter->second.end(), mesh);
        if (meshIter != vectorIter->second.end())
            vectorIter->second.erase(meshIter);
    }
}

Texture* Renderer::GetTexture(const std::string& filename) {
    Texture* tex = nullptr;
    auto iter = mTextures.find(filename);
    if (iter != mTextures.end()) {
        tex = iter->second;
    } else {
        tex = new Texture();
        if (tex->Load(filename)) {
            mTextures.emplace(filename, tex);
        } else {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName) {
    Mesh* m = nullptr;
    auto iter = mMeshes.find(fileName);
    if (iter != mMeshes.end()) {
        m = iter->second;
    } else {
        m = new Mesh();
        if (m->Load(fileName, this)) {
            mMeshes.emplace(fileName, m);
        } else {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

Shader* Renderer::GetShader(const std::string& shaderName) {
    Shader* m = nullptr;
    auto iter = mShaders.find(shaderName);
    if (iter != mShaders.end()) {
        m = iter->second;
    } else {
        m = new Shader();
        if (m->Load(shaderName + ".vert", shaderName + ".frag")) {
            mShaders.emplace(shaderName, m);
        } else {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

Font* Renderer::GetFont(const std::string& fileName) {
    auto iter = mFonts.find(fileName);
    if (iter != mFonts.end()) {
        return iter->second;
    } else {
        Font* font = new Font();
        if (font->Load(fileName)) {
            mFonts.emplace(fileName, font);
        } else {
            font->Unload();
            delete font;
            font = nullptr;
        }
        return font;
    }
}

bool Renderer::LoadShaders() {
    mSpriteShader = new Shader();

    if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag")) {
        return false;
    }

    mSpriteShader->SetActive();

    // ビュー射影行列の情報を流し込む
    Matrix4 viewProj =
        Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
    mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

    // Set the view-projection matrix
    mView =
        Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    mProjection = Matrix4::CreatePerspectiveFOV(
        Math::ToRadians(70.0f), mScreenWidth, mScreenHeight, 25.0f, 10000.0f);

    return true;
}

void Renderer::CreateSpriteVerts() {
    float vertexBuffer[] = {
        -0.5f, 0.5f,  0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,  // top left
        0.5f,  0.5f,  0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,  // top right
        0.5f,  -0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,  // bottom right
        -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f   // bottom left
    };

    unsigned int indexBuffer[] = {0, 1, 2, 2, 3, 0};

    mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

//ShaderファイルはGLSLへの架け橋の役目，光のセットアップを書いてしまうとそれが崩れる
void Renderer::SetLightUniforms(Shader* shader) {
    // Camera position is from inverted view
    Matrix4 invView = mView;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    // Ambient light
    shader->SetVectorUniform("uAmbientLight", mAmbientLight);
    // Directional light
    shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
    shader->SetVectorUniform("uDirLight.mDiffuseColor",
                             mDirLight.mDiffuseColor);
    shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}

/*
現在の実装では，configの項目が少ないため，項目で分岐させて列挙体のTypeIDで管理するので十分
メリット: どのIDがどの設定が分かるため，デバッグが容易
デメリット: 設定項目が多くなると，実装が煩雑．スケールしない．
設定項目が多くなってきたら，設定項目をハッシュ値に変換する実装に切り替える
メリット: 設定項目が多くても，実装がシンプル．
デメリット: ハッシュ値に変換すると，元の設定内容が分からないため，デバッグに工夫が必要．
ハッシュ値を出力するようにする場合，描画順序を考慮させることが難しい．そのため上位ピットのいくつかは描画順序を表す数字にして，mapの描画順序を表す
*/
ConfigID Renderer::GetConfigID(const RenderConfig& config) {
    ConfigID id;
    if (config.mCullFaceBack) {
        id = ConfigID::Dome;
    } else if (config.mBlend && !config.mDepthMask && config.mDepthTest) {
        id = ConfigID::Translucent;
    } else {
        id = ConfigID::Opaque;
    }
    mMeshConfigs.emplace(id, config);
    return id;
}
