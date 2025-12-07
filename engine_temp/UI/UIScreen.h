#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "core/Math.h"

class UIScreen {
   public:
    // ClosingだとUIに対して操作できない
    enum UIState { EActive, EClosing };

   protected:
    void DrawTexture(class Shader* shader, class Texture* texture,
                     const Vector2& offset = Vector2::Zero, float scale = 1.0f);

    class Game* mGame;
    class Font* mFont;
    // UIに表示する文字列？
    class Texture* mTitle;
    Vector2 mTitlePos;
    // 状態
    UIState mState;

   public:
    UIScreen(class Game* game);
    virtual ~UIScreen();

    // 派生クラスで処理を決められる
    virtual void Update(float deltaTime) {};
    virtual void Draw(class Shader* shader);
    virtual void ProcessInput(const class InputState& state);
    virtual void HandleKeyPress(int key);

    //状態をClosingにする
    void Close() { mState = EClosing; };
    UIState GetState() const { return mState; }

    void SetTitle(const std::string& text, const Vector3& color = Color::White,
                  int pointSize = 40);
};
