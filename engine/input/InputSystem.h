#pragma once
#include "KeyboardState.h"
#include "MouseState.h"
#include "SDL.h"

// 現在の入力状態を格納するラッパー
struct InputState {
    KeyboardState Keyboard;
    MouseState Mouse;
};

// 入力の状態を管理
class InputSystem {
    InputState mState;

   public:
    bool Initialize();
    void Shutdown();

    // ポーリングではなく，イベントドリブンで入力状態を受け取る
    void ProcessEvent(SDL_Event& event);

    // 入力状態は前の状態からの変化を求められる場合もあるため，前処理で前の状態を保存する必要がある
    // SDL_PollEventsループの直前に呼ばれる
    void PrepareForUpdate();
    // SDL_PollEventsループの直後に呼ばれる
    void Update();

    const InputState& GetState() const { return mState; }

    // 相対マウスモードを有効 / 無効
    void SetRelativeMouseMode(bool value);
};
