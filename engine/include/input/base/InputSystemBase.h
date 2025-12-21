#pragma once
#include "IInputSystem.h"

// 入力の状態を管理
/*
    InputState: 入力情報を格納
*/
template <typename InputState>
class InputSystemBase : public IInputSystem {
    static_assert(std::is_base_of<InputStateBase, InputState>::value,
                  "InputState must derive from InputStateBase");

   protected:
    InputState mState;

   public:
    InputSystemBase() = default;
    virtual ~InputSystemBase() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    // 更新処理
    // 入力状態を定期的に問い合わせる (ポーリング)
    virtual void Update() = 0;

    // Engineで使われるためのエントリポイント
    void IUpdate() final { Update(); }

    const struct InputStateBase& IGetState() const final { return mState; }
};
