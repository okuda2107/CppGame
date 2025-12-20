#pragma once

// 入力の状態を管理
/*
    InputState: 入力情報を格納
*/
template <typename InputState>
class InputSystemBase {
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

    const InputState& GetState() const { return mState; }
};
