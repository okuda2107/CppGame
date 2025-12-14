#pragma once
#include "InputState.h"
#include "SDL.h"
#include "input/InputSystemBase.h"

namespace KeyboardAndMouse {
// 入力の状態を管理
class InputSystem : public InputSystemBase<InputState> {
   public:
    InputSystem();

    bool Initialize();
    void Shutdown();

    // 入力状態更新処理
    void Update();

    // 相対マウスモードを有効 / 無効
    void SetRelativeMouseMode(bool value);
};
}  // namespace KeyboardAndMouse
