#pragma once
#include <cstdint>

#include "LevelLoader.h"
#include "MoveComponent.h"
#include "SDL.h"

class InputComponent : public MoveComponent {
    float mMaxForwardSpeed;
    float mMaxStrafeSpeed;
    float mMaxYawSpeed;

    const static int mForwardKey = SDL_SCANCODE_W;
    const static int mBackKey = SDL_SCANCODE_S;

    const static int mRightKey = SDL_SCANCODE_D;
    const static int mLeftKey = SDL_SCANCODE_A;

    const static int mTurnKey = SDL_SCANCODE_J;
    const static int mOppositeTurnKey = SDL_SCANCODE_L;

   public:
    InputComponent(class Actor* owner);
    void ProcessInput(const uint8_t* keystate);

    void SetMaxForwardSpeed(float maxFowardSpeed) {
        mMaxForwardSpeed = maxFowardSpeed;
    }
    void SetMaxStrafeSpeed(float maxStrafeSpeed) {
        mMaxStrafeSpeed = maxStrafeSpeed;
    }

    void SetMaxYawSpeed(float maxYawSpeed) { mMaxYawSpeed = maxYawSpeed; }

    TypeID GetType() const { return TypeID::TInputComponent; }
};
