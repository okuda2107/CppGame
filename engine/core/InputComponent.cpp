#include "InputComponent.h"

InputComponent::InputComponent(class Actor* owner) : MoveComponent(owner) {}

void InputComponent::ProcessInput(const uint8_t* keystate) {
    float fowardSpeed = 0.0f;
    if (keystate[mForwardKey]) fowardSpeed += mMaxForwardSpeed;
    if (keystate[mBackKey]) fowardSpeed -= mMaxForwardSpeed;
    SetForwardSpeed(fowardSpeed);

    float rightSpeed = 0.0f;
    if (keystate[mRightKey]) rightSpeed += mMaxStrafeSpeed;
    if (keystate[mBackKey]) rightSpeed -= mMaxStrafeSpeed;
    SetYAngularSpeed(rightSpeed);

    float yawSpeed = 0.0f;
    if (keystate[mTurnKey]) yawSpeed += mMaxYawSpeed;
    if (keystate[mOppositeTurnKey]) yawSpeed -= mMaxYawSpeed;
    SetZAngularSpeed(yawSpeed);
}
