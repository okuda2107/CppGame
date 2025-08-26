#pragma once
#include "KeyboardState.h"
#include "SDL.h"

// 現在の入力状態を格納するラッパー
struct InputState {
    KeyboardState Keyboard;
};

class InputSystem {
    InputState mState;

   public:
    bool Initialize();
    void Shutdown();

    // SDL_PollEventsループの直前に呼ばれる
    void PrepareForUpdate();
    // SDL_PollEventsループの直後に呼ばれる
    void Update();

    const InputState& GetState() const { return mState; }
};
