#include "InputComponent.h"

#include "InputSystem.h"

InputComponent::InputComponent(class Actor* owner) : MoveComponent(owner) {}

void InputComponent::ProcessInput(const InputState& state) {
    float fowardSpeed = 0.0f;
    if (state.Keyboard.GetKeyValue(mForwardKey))
        fowardSpeed += mMaxForwardSpeed;
    if (state.Keyboard.GetKeyValue(mBackKey)) fowardSpeed -= mMaxForwardSpeed;
    SetForwardSpeed(fowardSpeed);

    float rightSpeed = 0.0f;
    if (state.Keyboard.GetKeyValue(mRightKey)) rightSpeed += mMaxStrafeSpeed;
    if (state.Keyboard.GetKeyValue(mLeftKey)) rightSpeed -= mMaxStrafeSpeed;
    SetRightSpeed(rightSpeed);

    const int maxMouseSpeed = 500;
    const float maxAngularSpeed = Math::Pi * 8;
    float yawSpeed = 0;
    Vector2 mousePos = state.Mouse.GetPostion();
    if (!Math::NearZero(mousePos.x)) {
        yawSpeed = static_cast<float>(mousePos.x) / maxMouseSpeed;
        yawSpeed *= maxAngularSpeed;
    }
    SetYawSpeed(yawSpeed);
}
