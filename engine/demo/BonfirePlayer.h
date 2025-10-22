#pragma once
#include "Bonfire.h"
#include "ContextComponent.h"
#include "FPSActor.h"

// フィールドによる位置の制限とアニメーション機能を付けたクラス
class BonfirePlayer : public FPSActor {
    bool mIsAnimLookUp;
    bool mIsAnimLookDown;
    // 0未満なら初期値
    float mLookUpEndTime;
    float mLookDownEndTime;

    // 木生成器
    class WoodGenerator* mGenerator;

    //UI
    class UIScreen* mUI;

    // 木を持っているか
    bool mHasWood;

    class ContextComponent<Bonfire>* cc;

    // コルーチンハンドラ
    class Coroutine* mCoroutines;

    // 視線を上げる / 下げる アニメーション
    static float Ease(float t);
    void PitchUp(float lerp);
    void PitchDown(float lerp);

   public:
    BonfirePlayer(class Game* game);
    ~BonfirePlayer();

    void ActorInput(const InputState& state) override;
    void UpdateActor(float deltatime) override;

    // title押されてからの初期化処理
    void Initialize();

    void SetAnimLookUp() { mIsAnimLookUp = true; }
    void SetAnimLookDown() { mIsAnimLookDown = true; }
    bool GetAnimLookUp() { return mIsAnimLookUp; }

    void SetContext(class Bonfire* actor) { cc->SetActor(actor); }
};
