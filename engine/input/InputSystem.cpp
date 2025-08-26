#include "InputSystem.h"

bool InputSystem::Initialize() {
    // 現在の状態を示すポインタを保存
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
    // 前回の状態を示すメモリをクリア
    memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

    return true;
}

void InputSystem::Shutdown() {}

void InputSystem::PrepareForUpdate() {
    memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState,
           SDL_NUM_SCANCODES);
}

void InputSystem::Update() {}
