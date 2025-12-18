#pragma once
#include <string>
#include <unordered_map>

#include "core/Math.h"

class UIScreen {
   public:
    // ClosingだとUIに対して操作できない
    enum UIState { EActive, EClosing };

   protected:
    class UISystem* mSystem;

    UIState mState;

    class Font* mFont;
    // フォントをテクスチャに変換した結果
    std::unordered_map<std::string, class Texture*> mFontTexture;

    void DrawTexture(class Shader* shader, class Texture* texture,
                     const Vector2& offset = Vector2::Zero, float scale = 1.0f);

   public:
    UIScreen(class UISystem* manager);
    virtual ~UIScreen();

    virtual void Load() = 0;

    // 派生クラスで処理を決められる
    virtual void Update(float deltaTime) {};
    virtual void Draw(class Shader* shader) = 0;
    virtual void ProcessInput(const class InputState& state) {};
    virtual void HandleKeyPress(int key) {};

    //状態をClosingにする
    void Close() { mState = EClosing; }
    UIState GetState() const { return mState; }
};
