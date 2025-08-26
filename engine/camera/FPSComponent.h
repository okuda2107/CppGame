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
    // pitchの入力角速度
    float mInputPitchSpeed;
    ;

    // pitchの操作キー
    const static SDL_Scancode mLookUpKey = SDL_SCANCODE_K;
    const static SDL_Scancode mLookDownKey = SDL_SCANCODE_I;

   public:
    FPSComponent(class Actor* owner, int drawOrder = 200);
    ~FPSComponent();

    void ProcessInput(const class InputState& keystate) override;
    void Update(float deltatime) override;

    void SetMaxPitch(float maxPitch) { mMaxPitch = maxPitch; }
    void SetInputPitchSpeed(float inputPitchSpeed) {
        mInputPitchSpeed = inputPitchSpeed;
    }

    TypeID GetType() const { return TypeID::TFPSComponent; }
};
