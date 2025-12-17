#pragma once
#include <vector>

// 入力の状態を管理
/*
    InputComponent: Actorに入力情報を伝えるためのComponent
    InputState: 入力情報を格納
*/
template <typename InputState>
class InputSystemBase {
   protected:
    InputState mState;

   public:
    InputSystemBase() {}
    virtual ~InputSystemBase() {}

    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    // 更新処理
    // 入力状態を定期的に問い合わせる (ポーリング)
    virtual void Update() = 0;

    const InputState& GetState() const { return mState; }
};
