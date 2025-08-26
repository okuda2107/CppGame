#pragma once
#include <cstdint>

#include "LevelLoader.h"
#include "MoveComponent.h"
#include "SDL.h"

class InputComponent : public MoveComponent {
    float mMaxForwardSpeed;
    float mMaxStrafeSpeed;
    float mMaxYawSpeed;

    const static SDL_Scancode mForwardKey = SDL_SCANCODE_W;
    const static SDL_Scancode mBackKey = SDL_SCANCODE_S;

    const static SDL_Scancode mRightKey = SDL_SCANCODE_D;
    const static SDL_Scancode mLeftKey = SDL_SCANCODE_A;

    const static SDL_Scancode mTurnKey = SDL_SCANCODE_L;
    const static SDL_Scancode mOppositeTurnKey = SDL_SCANCODE_J;

   public:
    InputComponent(class Actor* owner);
    void ProcessInput(const class InputState& keystate);

    void SetMaxForwardSpeed(float maxFowardSpeed) {
        mMaxForwardSpeed = maxFowardSpeed;
    }
    void SetMaxStrafeSpeed(float maxStrafeSpeed) {
        mMaxStrafeSpeed = maxStrafeSpeed;
    }

    void SetMaxYawSpeed(float maxYawSpeed) { mMaxYawSpeed = maxYawSpeed; }

    TypeID GetType() const { return TypeID::TInputComponent; }
};
