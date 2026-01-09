#pragma once
#include "game/camera/FPSActor.h"

struct BonfirePlayerDeps : FPSActorDeps {
    class ActorsSystem& actorsSystem;

    BonfirePlayerDeps(class ActorsSystem& actorsSystem,
                      class RenderDB& renderDB, class AudioSystem& audioSystem)
        : FPSActorDeps(renderDB, audioSystem), actorsSystem(actorsSystem) {}
};

// フィールドによる位置の制限とアニメーション機能を付けたクラス
// 初期化処理として，フィールドの範囲をセットする必要がある．
class BonfirePlayer : public FPSActor {
    bool mIsAnimLookUp;
    bool mIsAnimLookDown;
    // 0未満なら初期値
    float mLookUpEndTime;
    float mLookDownEndTime;

    // 木生成器
    ActorID mGeneratorID;

    //UI
    // 木に関するUIを保持
    class UIScreen* mWoodUI;
    // たき火に関するUIを保持
    class UIScreen* mBonfireUI;

    // 木を持っているか
    bool mHasWood;

    ActorID mBonfireID;

    // コルーチンハンドラ
    class Coroutine* mCoroutines;

    // 視線を上げる / 下げる アニメーション
    static float Ease(float t);
    void PitchUp(float lerp);
    void PitchDown(float lerp);

    Vector2& mFieldMin;
    Vector2& mFieldMax;

    // todo: 他Actorと依存してしまっているので，これが必要．衝突検知などを他のところで行えたらこれは必要なくなるかもしれない
    class ActorsSystem& mActorsSystem;

   public:
    BonfirePlayer(class ActorsSystem* system, BonfirePlayerDeps deps);
    ~BonfirePlayer();

    void ActorInput(const InputState& state) override;
    void UpdateActor(float deltatime) override;

    // title押されてからの初期化処理
    void Initialize();

    void SetAnimLookUp() { mIsAnimLookUp = true; }
    void SetAnimLookDown() { mIsAnimLookDown = true; }
    bool GetAnimLookUp() { return mIsAnimLookUp; }

    void SetBonfireID(ActorID id) { mBonfireID = id; }

    // Playerが動ける範囲を指定
    void SetFieldRange(Vector2& fieldMin, Vector2& fieldMax) {
        mFieldMin = fieldMin;
        mFieldMax = fieldMax;
    }
};
