#include "BonfirePlayer.h"

#include "Coroutine.h"

BonfirePlayer::BonfirePlayer(class Game* game)
    : FPSActor(game),
      mIsAnimLookUp(false),
      mIsAnimLookDown(false),
      mLookUpEndTime(-1.0f),
      mLookDownEndTime(-1.0f) {
    mCoroutines = new Coroutine();
}

void BonfirePlayer::ActorInput(const InputState& state) {
    // アニメーション中は操作を受け付けない
    if (mIsAnimLookUp || mIsAnimLookDown) return;
    FPSActor::ActorInput(state);
}

void BonfirePlayer::UpdateActor(float deltatime) {
    mCoroutines->Update(deltatime);
    if (mIsAnimLookUp) {
        if (mLookUpEndTime < 0)
            mLookUpEndTime = mCoroutines->AddCoroutine(
                2.0, [this](float t) { this->PitchUp(t); });
        if (mCoroutines->CheckCoroutine(mLookUpEndTime)) {
            mIsAnimLookUp = false;
            mLookUpEndTime = -1.0f;
        }
    } else if (mIsAnimLookDown) {
        if (mLookDownEndTime < 0)
            mLookDownEndTime = mCoroutines->AddCoroutine(
                2.0, [this](float t) { this->PitchDown(t); });
        if (mCoroutines->CheckCoroutine(mLookDownEndTime)) {
            mIsAnimLookDown = false;
            mLookDownEndTime = -1.0f;
        }
    }
    FPSActor::UpdateActor(deltatime);

    // 位置の制限
    Vector3 pos = GetPosition();
    pos.x = Math::Clamp(pos.x, -100.0f, 100.0f);
    pos.y = Math::Clamp(pos.y, -100.0f, 100.0f);
    SetPosition(pos);
}

float BonfirePlayer::Ease(float t) { return 0.5f * (1 - cosf(Math::Pi * t)); }

// カメラの視線を下げる
void BonfirePlayer::PitchDown(float lerp) {
    float t = Ease(lerp);
    SetPitchAngular(Math::Lerp(-Math::Pi / 4, 0, t));
}

// カメラの視線を上げる
void BonfirePlayer::PitchUp(float lerp) {
    float t = Ease(lerp);
    SetPitchAngular(Math::Lerp(0, -Math::Pi / 4, t));
}
