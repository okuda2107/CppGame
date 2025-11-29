#include "Input2DComponent.h"

#include "InputSystem.h"

Input2DComponent::Input2DComponent(class Actor* owner) : MoveComponent(owner) {}

// todo: 2Dにするともしかしたら実装を変えやなあかんかもしれん
void Input2DComponent::ProcessInput(const InputState& state) {
    float fowardSpeed = 0.0f;
    if (state.Keyboard.GetKeyValue(mForwardKey))
        fowardSpeed += mMaxForwardSpeed;
    if (state.Keyboard.GetKeyValue(mBackKey)) fowardSpeed -= mMaxForwardSpeed;
    SetForwardSpeed(fowardSpeed);

    float rightSpeed = 0.0f;
    if (state.Keyboard.GetKeyValue(mRightKey)) rightSpeed += mMaxStrafeSpeed;
    if (state.Keyboard.GetKeyValue(mLeftKey)) rightSpeed -= mMaxStrafeSpeed;
    SetRightSpeed(rightSpeed);
}
