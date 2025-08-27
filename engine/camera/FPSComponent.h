#pragma once
#include "CameraComponent.h"
#include "SDL.h"

// FPS視点の位置にカメラをアタッチする
class FPSComponent : public CameraComponent {
    // pitchのみActorに依存していないので，変数を持つ必要がある．
    // 現在のpitch
    float mPitch;
    // pitchの最大角度
    float mMaxPitch;
    // pitchの角速度
    float mPitchSpeed;

   public:
    FPSComponent(class Actor* owner, int drawOrder = 200);
    ~FPSComponent();

    void Update(float deltatime) override;

    float GetPitch() const { return mPitch; }

    void SetPitchSpeed(float pitchSpeed) { mPitchSpeed = pitchSpeed; }
    void SetMaxPitch(float maxPitch) { mMaxPitch = maxPitch; }

    TypeID GetType() const { return TypeID::TFPSComponent; }
};
