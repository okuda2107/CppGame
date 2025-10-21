#pragma once
#include "FPSActor.h"

// フィールドによる位置の制限とアニメーション機能を付けたクラス
class BonfirePlayer : public FPSActor {
    bool mIsAnimLookUp;
    bool mIsAnimLookDown;
    // 0未満なら初期値
    float mLookUpEndTime;
    float mLookDownEndTime;

    // コルーチンハンドラ
    class Coroutine* mCoroutines;

    // 視線を上げる / 下げる アニメーション
    void PitchUp(float lerp);
    void PitchDown(float lerp);

   public:
    BonfirePlayer(class Game* game);

    void ActorInput(const InputState& state) override;
    void UpdateActor(float deltatime) override;

    void SetAnimLookUp() { mIsAnimLookUp = true; }
    void SetAnimLookDown() { mIsAnimLookDown = true; }
    bool GetAnimLookUp() { return mIsAnimLookUp; }
};
