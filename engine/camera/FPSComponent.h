#pragma once
#include "CameraComponent.h"
#include "SDL.h"

class FPSComponent : public CameraComponent {
    // 現在のpitch
    float mPitch;
    // pitchの最大角度
    float mMaxPitch;
    // pitchの角速度
    float mPitchSpeed;
    // 現在の入力状況 0 or 1 or -1
    float mInput;

    // pitchの操作キー
    const static SDL_Scancode mLookUpKey = SDL_SCANCODE_K;
    const static SDL_Scancode mLookDownKey = SDL_SCANCODE_I;

   public:
    FPSComponent(class Actor* owner, int drawOrder = 200);
    ~FPSComponent();

    void ProcessInput(const class InputState& keystate) override;
    void Update(float deltatime) override;

    void SetMaxPitch(float maxPitch) { mMaxPitch = maxPitch; }
    void SetPitchSpeed(float pitchSpeed) { mPitchSpeed = pitchSpeed; }

    TypeID GetType() const { return TypeID::TFPSComponent; }
};
