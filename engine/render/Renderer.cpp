#include "Renderer.h"

#include <algorithm>

#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Shader.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "VertexArray.h"
#include "glew.h"

Renderer::Renderer(class Game* game)
    : mGame(game),
      mContext(nullptr),
      mScreenHeight(0.0f),
      mScreenWidth(0.0f),
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

    // メッシュ描画
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    for (auto shader : mShaders) {
        shader.second->SetActive();
        shader.second->SetMatrixUniform("uViewProj", mView * mProjection);
        SetLightUniforms(shader.second);
        for (auto mc : mMeshComps) {
            mc->Draw(shader.first, shader.second);
        }
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

void Renderer::AddMeshComp(MeshComponent* mesh) {
    mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh) {
    auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
    mMeshComps.erase(iter);
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
        -0.5f, 0.5f,  0.f, 0.f, 0.f,  // top left
        0.5f,  0.5f,  0.f, 1.f, 0.f,  // top right
        0.5f,  -0.5f, 0.f, 1.f, 1.f,  // bottom right
        -0.5f, -0.5f, 0.f, 0.f, 1.f   // bottom left
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
