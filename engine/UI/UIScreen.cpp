#include "UIScreen.h"

#include "Font.h"
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "glew.h"

UIScreen::UIScreen(Game* game)
    : mGame(game), mTitle(nullptr), mTitlePos(0.0f, 300.0f), mState(EActive) {
    // Add to UI Stack
    mGame->PushUI(this);
    mFont = mGame->GetFont("Assets/SlacksideOne-Regular.ttf");
}

UIScreen::~UIScreen() {
    if (mTitle) {
        mTitle->Unload();
        delete mTitle;
    }
}

void UIScreen::Draw(Shader* shader) {
    if (mTitle) {
        DrawTexture(shader, mTitle, mTitlePos);
    }
}

void UIScreen::ProcessInput(const InputState& state) {}

void UIScreen::HandleKeyPress(int key) {}

void UIScreen::SetTitle(const std::string& text, const Vector3& color,
                        int pointSize) {
    // 古い文字テクスチャのリソースを解放してから新しい文字テクスチャを取得する
    if (mTitle) {
        mTitle->Unload();
        delete mTitle;
        mTitle = nullptr;
    }
    mTitle = mFont->RenderText(text, color, pointSize);
}

void UIScreen::DrawTexture(class Shader* shader, class Texture* texture,
                           const Vector2& offset, float scale) {
    // Scale the quad by the width/height of texture
    Matrix4 scaleMat = Matrix4::CreateScale(
        static_cast<float>(texture->GetWidth()) * scale,
        static_cast<float>(texture->GetHeight()) * scale, 1.0f);
    // Translate to position on screen
    Matrix4 transMat =
        Matrix4::CreateTranslation(Vector3(offset.x, offset.y, 0.0f));
    // Set world transform
    Matrix4 world = scaleMat * transMat;
    shader->SetMatrixUniform("uWorldTransform", world);
    // Set current texture
    texture->SetActive();
    // Draw quad

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
