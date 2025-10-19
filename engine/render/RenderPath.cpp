#include "RenderPath.h"

#include "Renderer.h"
#include "SDL.h"
#include "Shader.h"

// todo: エンジン内でFBOをどのように扱うかは要検討
// わざわざRender Bufferに固定化しなくてもいいような気がする
// とりあえずポストエフェクトを実装するためこれはこのままで扱う
RenderPath::RenderPath(class Renderer* renderer, std::string effectName)
    : mRenderer(renderer), mShaderName(effectName) {
    // effectに使うshaderをロード
    renderer->GetShader(effectName);
}

RenderPath::~RenderPath() {}

bool RenderPath::Load() {
    float width = mRenderer->GetScreenWidth();
    float height = mRenderer->GetScreenHeight();

    // FBO作成
    glGenFramebuffers(1, &mBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mBuffer);

    // カラーアタッチメント（テクスチャ）
    glGenTextures(1, &mColorBuffer);
    glBindTexture(GL_TEXTURE_2D, mColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindFramebuffer(GL_FRAMEBUFFER, mBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           mColorBuffer, 0);

    // 深度アタッチメント（テクスチャ）
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                          static_cast<int>(width), static_cast<int>(height));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, mDepthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           mDepthBuffer, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 完成チェック
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        SDL_Log("Error: RenderPath FBO not complete\n");
        return false;
    }

    return true;
}

void RenderPath::Unload() {
    glDeleteFramebuffers(1, &mBuffer);
    glDeleteTextures(1, &mColorBuffer);
    glDeleteTextures(1, &mDepthBuffer);
}

void RenderPath::SetActive() {
    glBindFramebuffer(GL_FRAMEBUFFER, mBuffer);
    glViewport(0, 0, mRenderer->GetScreenWidth(), mRenderer->GetScreenHeight());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderPath::BlitToScreen() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    // shaderの有効化
    Shader* shader = mRenderer->GetShader(mShaderName);
    if (shader) shader->SetActive();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mColorBuffer);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
}
