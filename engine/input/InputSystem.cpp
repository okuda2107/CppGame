#include "InputSystem.h"

bool InputSystem::Initialize() {
    // キーボード
    // 現在の状態を示すポインタを保存
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
    // 前回の状態を示すメモリをクリア
    memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

    // マウス
    // SDL_ShowCursor(SDL_FALSE);
    SDL_ShowCursor(SDL_TRUE);
    mState.Mouse.mIsRelative = false;

    return true;
}

void InputSystem::Shutdown() {}

void InputSystem::ProcessEvent(SDL_Event& event) {
    switch (event.type) {
        case SDL_MOUSEWHEEL:
            mState.Mouse.mScrollWheel =
                Vector2(static_cast<float>(event.wheel.x),
                        static_cast<float>(event.wheel.y));
            break;
    }
}

void InputSystem::PrepareForUpdate() {
    // キーボード
    memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState,
           SDL_NUM_SCANCODES);

    // マウス
    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
    mState.Mouse.mScrollWheel = Vector2::Zero;
}

void InputSystem::Update() {
    // マウス
    int x = 0, y = 0;
    if (mState.Mouse.mIsRelative) {
        mState.Mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
    } else {
        mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
    }
    mState.Mouse.mMousePos.x = static_cast<float>(x);
    mState.Mouse.mMousePos.y = static_cast<float>(y);
}

void InputSystem::SetRelativeMouseMode(bool value) {
    SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
    SDL_SetRelativeMouseMode(set);
    mState.Mouse.mIsRelative = value;
}
