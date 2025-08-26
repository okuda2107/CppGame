#include "InputComponent.h"

#include "InputSystem.h"

InputComponent::InputComponent(class Actor* owner) : MoveComponent(owner) {}

void InputComponent::ProcessInput(const InputState& keystate) {
    float fowardSpeed = 0.0f;
    if (keystate.Keyboard.GetKeyValue(mForwardKey))
        fowardSpeed += mMaxForwardSpeed;
    if (keystate.Keyboard.GetKeyValue(mBackKey))
        fowardSpeed -= mMaxForwardSpeed;
    SetForwardSpeed(fowardSpeed);

    float rightSpeed = 0.0f;
    if (keystate.Keyboard.GetKeyValue(mRightKey)) rightSpeed += mMaxStrafeSpeed;
    if (keystate.Keyboard.GetKeyValue(mLeftKey)) rightSpeed -= mMaxStrafeSpeed;
    SetRightSpeed(rightSpeed);

    float yawSpeed = 0.0f;
    if (keystate.Keyboard.GetKeyValue(mTurnKey)) yawSpeed += mMaxYawSpeed;
    if (keystate.Keyboard.GetKeyValue(mOppositeTurnKey))
        yawSpeed -= mMaxYawSpeed;
    SetYawSpeed(yawSpeed);
}
