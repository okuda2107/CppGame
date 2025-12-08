#pragma once
#include "SDL.h"
#include "input/Button/ButtonState.h"

namespace KeyboardAndMouse {
class InputSystem;
}

class KeyboardState {
    friend KeyboardAndMouse::InputSystem;

    // 現在の状態
    const Uint8* mCurrState;
    // 1つ前のフレームの状態
    Uint8 mPrevState[SDL_NUM_SCANCODES];

   public:
    // キーの真偽値のみを取得する
    bool GetKeyValue(SDL_Scancode keyCode) const;
    // 現在と，その1つ前のフレームから状態を取得
    ButtonState GetKeyState(SDL_Scancode keyCode) const;
};
