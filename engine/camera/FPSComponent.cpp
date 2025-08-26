#include "FPSComponent.h"

#include "Actor.h"
#include "AudioSystem.h"
#include "Game.h"
#include "Math.h"
#include "Renderer.h"

FPSComponent::FPSComponent(class Actor* owner, int updateOrder)
    : CameraComponent(owner, updateOrder),
      mPitch(0.0f),
      mMaxPitch(0.0f),
      mPitchSpeed(0.0f),
      mInput(0) {}

FPSComponent::~FPSComponent() {}

void FPSComponent::ProcessInput(const uint8_t* keystate) {
    mInput = 0;
    if (keystate[mLookUpKey]) mInput = 1;
    if (keystate[mLookDownKey]) mInput = -1;
}

void FPSComponent::Update(float deltatime) {
    CameraComponent::Update(deltatime);
    // カメラの位置は所有アクターの位置
    Vector3 cameraPos = mOwner->GetPosition();

    // pitchの角速度に基づいてpitchを更新
    mPitch += mPitchSpeed * mInput * deltatime;
    // pitchを最大角度の範囲に収める
    mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
    // pitch回転を表すクォータニオン
    Quaternion q(mOwner->GetRight(), mPitch);

    // 所有アクターの前方ベクトルを回転
    Vector3 viewForward = Vector3::Transform(mOwner->GetForward(), q);
    // targetの位置は所有アクターの前方100単位
    Vector3 target = cameraPos + viewForward * 100.0f;

    // 上方ベクトルを回転
    Vector3 up = Vector3::Transform(mOwner->GetUp(), q);

    // 注視行列を作って，viewに設定
    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
    SetViewMatrix(view);
}
