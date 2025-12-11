#pragma once
#include "KeyboardState.h"
#include "MouseState.h"

// 入力機器から取得した情報をまとめた構造体
namespace KeyboardAndMouse {
struct InputState {
    class KeyboardState* Keyboard;
    class MouseState* Mouse;

    InputState();
};
}  // namespace KeyboardAndMouse
