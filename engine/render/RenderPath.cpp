#include "RenderPath.h"

#include "Renderer.h"
#include "SDL.h"
#include "Shader.h"
#include "VertexArray.h"

// todo: エンジン内でFBOをどのように扱うかは要検討
// わざわざRender Bufferに固定化しなくてもいいような気がする
// とりあえずポストエフェクトを実装するためこれはこのままで扱う
RenderPath::RenderPath(class Renderer* renderer) : mRenderer(renderer) {}

RenderPath::~RenderPath() {}

bool RenderPath::Load() {
    int width = static_cast<int>(mRenderer->GetScreenWidth());
    int height = static_cast<int>(mRenderer->GetScreenHeight());

    // FBO作成
    glGenFramebuffers(1, &mBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mBuffer);

    // カラーアタッチメント（テクスチャ）
    glGenTextures(1, &mColorBuffer);
    glBindTexture(GL_TEXTURE_2D, mColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA,
                 GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           mColorBuffer, 0);

    // 深度アタッチメント
    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER, mDepthBuffer);

    // 完成チェック
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        SDL_Log("Error: RenderPath FBO not complete\n");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    // 一時バッファを作成
    // 一時FBO
    glGenFramebuffers(1, &mTempBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mTempBuffer);

    // 一時テクスチャ
    glGenTextures(1, &mTempColorBuffer);
    glBindTexture(GL_TEXTURE_2D, mTempColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA,
                 GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           mTempColorBuffer, 0);

    // 完成チェック
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        SDL_Log("Error: RenderPath FBO not complete\n");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

void RenderPath::Unload() {
    glDeleteFramebuffers(1, &mBuffer);
    glDeleteTextures(1, &mColorBuffer);
    glDeleteRenderbuffers(1, &mDepthBuffer);
    glDeleteFramebuffers(1, &mTempBuffer);
    glDeleteTextures(1, &mTempColorBuffer);
}

void RenderPath::AddEffect(class Shader* shader) { mEffects.push_back(shader); }

void RenderPath::SetActive() {
    glBindFramebuffer(GL_FRAMEBUFFER, mBuffer);
    glViewport(0, 0, static_cast<int>(mRenderer->GetScreenWidth()),
               static_cast<int>(mRenderer->GetScreenHeight()));
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderPath::ApplyEffect(class VertexArray* va) {
    int width = static_cast<int>(mRenderer->GetScreenWidth());
    int height = static_cast<int>(mRenderer->GetScreenHeight());

    va->SetActive();

    for (auto shader : mEffects) {
        // 1. 書き込み先を仮バッファに変更
        glBindFramebuffer(GL_FRAMEBUFFER, mTempBuffer);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. 入力として現在のmColorBufferをセット
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mColorBuffer);

        shader->SetActive();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // 3. 結果をメインにコピー
        glBindFramebuffer(GL_READ_FRAMEBUFFER, mTempBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mBuffer);
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // 4. 仮バッファをクリア（必要なら）
        glBindFramebuffer(GL_FRAMEBUFFER, mTempBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);  // 戻す
}
