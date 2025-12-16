#pragma once
#include "core/Actor.h"

namespace KeyboardAndMouse {
class InputComponent;
}

namespace OpenGL {
class Font;
}

class UIScreen : public Actor {
   public:
    // ClosingだとUIに対して操作できない
    enum UIState { EActive, EClosing };

   protected:
    UIState mState;

    class UIComponent* mUIComp;
    KeyboardAndMouse::InputComponent* mInputComp;

    OpenGL::Font* mFont;

    void DrawTexture(OpenGL::Shader* shader, OpenGL::Texture* texture,
                     const Vector2& offset = Vector2::Zero, float scale = 1.0f);

   public:
    UIScreen(class ActorsSystem* actorSystem, class UIManager* manager,
             class Renderer* renderer);
    virtual ~UIScreen();

    // 派生クラスで処理を決められる
    virtual void Update(float deltaTime) {};
    virtual void Draw(OpenGL::Shader* shader);

    //状態をClosingにする
    void Close() { mState = EClosing; }
    UIState GetState() const { return mState; }
};
