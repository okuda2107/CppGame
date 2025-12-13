#pragma once
#include "InputState.h"
#include "SDL.h"
#include "input/InputSystemBase.h"

namespace KeyboardAndMouse {
typedef SDL_Event Event;
typedef SDL_EventType EventType;

constexpr EventType QUIT = SDL_QUIT;

constexpr EventType KEYDOWN = SDL_KEYDOWN;
constexpr EventType KEYUP = SDL_KEYUP;
constexpr EventType TEXTEDITING = SDL_TEXTEDITING;
constexpr EventType TEXTINPUT = SDL_TEXTINPUT;
constexpr EventType KEYMAPCHANGED = SDL_KEYMAPCHANGED;
constexpr EventType TEXTEDITING_EXT = SDL_TEXTEDITING_EXT;

constexpr EventType MOUSEMOTION = SDL_MOUSEMOTION;
constexpr EventType MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN;
constexpr EventType MOUSEBUTTONUP = SDL_MOUSEBUTTONUP;
constexpr EventType MOUSEWHEEL = SDL_MOUSEWHEEL;

// 入力の状態を管理
class InputSystem : public InputSystemBase<InputState> {
   public:
    InputSystem();

    bool Initialize();
    void Shutdown();

    // ポーリングではなく，イベントドリブンで入力状態を受け取る
    void ProcessEvent(Event& event);

    // 入力状態は前の状態からの変化を求められる場合もあるため，前処理で前の状態を保存する必要がある
    // SDL_PollEventsループの直前に呼ばれる
    void PrepareForUpdate();
    // SDL_PollEventsループの直後に呼ばれる
    void Update();

    const InputState& GetState() const { return mState; }

    // 相対マウスモードを有効 / 無効
    void SetRelativeMouseMode(bool value);
};

// SDLの関数をラップ
// eventとして飛んできた入力を受信する
int PollEvent(Event* event);
}  // namespace KeyboardAndMouse
