#include "UIScreen.h"

#include "Font.h"
#include "Game.h"
#include "Texture.h"

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

void UIScreen::Draw(Shader* shader) {}

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
