#include "Renderer.h"

#include <algorithm>

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "RenderPath.h"
#include "Shader.h"
#include "SkydomeComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "VertexArray.h"
#include "glew.h"

Renderer::Renderer(class Game* game)
    : mGame(game),
      mContext(nullptr),
      mScreenHeight(0.0f),
      mScreenWidth(0.0f),
      mSkydome(nullptr),
      mSpriteVerts(nullptr),
      mSpriteShader(nullptr),
      mWindow(nullptr) {}

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
        static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
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

    if (!LoadShaders()) {
        SDL_Log("Failed to Load Shaders");
        return false;
    }

    CreateSpriteVerts();

    CreatePostEffectVerts();

    return true;
}

void Renderer::Shutdown() {
    delete mSpriteVerts;
    mSpriteShader->Unload();
    delete mSpriteShader;
    delete mPostEffectVerts;
    mPostEffectMergeShader->Unload();
    delete mPostEffectMergeShader;
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

    for (auto i : mRenderPath) {
        i.second->Unload();
        delete i.second;
    }
    mRenderPath.clear();
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

    // 別パスで描画されたオブジェクトに効果を適用
    if (mRenderPath.size() > 0) {
        for (auto rp : mRenderPath) {
            rp.second->ApplyEffect(mPostEffectVerts);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        mPostEffectMergeShader->SetActive();
        mPostEffectVerts->SetActive();

        int index = 0;
        for (auto rp : mRenderPath) {
            glActiveTexture(GL_TEXTURE0 + index);
            glBindTexture(GL_TEXTURE_2D, rp.second->GetTextureIndex());
            ++index;
        }

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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

    // 別パスの指定
    if (config.effectName != "") {
        auto iter = mRenderPath.find(config.effectName);
        if (iter != mRenderPath.end()) iter->second->SetActive();
    }
}

void Renderer::ResetConfig() {
    // todo: 状態をリセットすることを検討
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_TRUE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
    auto iter = mMeshComps.find(id);
    if (iter != mMeshComps.end()) {
        mMeshComps.erase(iter);
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

// ポストエフェクトを適用するレンダリングパスを追加
// 現在の実装では，レンダリングパスの実装は開発者側が手動で追加しなければならない．
// 将来的にはMaterialクラスがその責務を担う？
RenderPath* Renderer::GetRenderPath(const std::string& effectName) {
    RenderPath* m = nullptr;
    auto iter = mRenderPath.find(effectName);
    if (iter != mRenderPath.end()) {
        m = iter->second;
    } else {
        m = new RenderPath(this);
        if (m->Load()) {
            mRenderPath.emplace(effectName, m);
        } else {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

bool Renderer::LoadShaders() {
    mSpriteShader = new Shader();

    if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag")) {
        return false;
    }

    mSpriteShader->SetActive();

    mPostEffectMergeShader = new Shader();

    if (!mPostEffectMergeShader->Load("Shaders/Merge.vert",
                                      "Shaders/Merge.frag")) {
        return false;
    }

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
        -0.5f, 0.5f,  0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  // top left
        0.5f,  0.5f,  0.f, 0.f, 0.f, 0.f, 1.f, 0.f,  // top right
        0.5f,  -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f,  // bottom right
        -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f,  // bottom left
    };

    unsigned int indexBuffer[] = {0, 1, 2, 2, 3, 0};

    mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

void Renderer::CreatePostEffectVerts() {
    float vertexBuffer[] = {
        -1.0f, 1.0f,  0.f, 0.f, 0.f, 0.f, 0.f, 1.f,  // top left
        1.0f,  1.0f,  0.f, 0.f, 0.f, 0.f, 1.f, 1.f,  // top right
        1.0f,  -1.0f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f,  // bottom right
        -1.0f, -1.0f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,  // bottom left
    };

    unsigned int indexBuffer[] = {0, 1, 2, 2, 3, 0};

    mPostEffectVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
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
