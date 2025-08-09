#include "InputComponent.h"

InputComponent::InputComponent(class Actor*owner) : MoveComponent(owner)
{}

void InputComponent::ProcessInput(const uint8_t* keystate)
{
	float xangularSpeed = 0.0f;
	if (keystate[xRotationKey])
	{
		xangularSpeed += mMaxAngularSpeed;
	}
	if (keystate[xAnti])
	{
		xangularSpeed -= mMaxAngularSpeed;
	}
	SetXAngularSpeed(xangularSpeed);
	float yangularSpeed = 0.0f;
	if (keystate[mForwardKey])
	{
		yangularSpeed += mMaxAngularSpeed;
	}
	if (keystate[mBackKey])
	{
		yangularSpeed -= mMaxAngularSpeed;
	}
	SetYAngularSpeed(yangularSpeed);

	float zangularSpeed = 0.0f;
	if (keystate[mClockwiseKey])
	{
		zangularSpeed += mMaxAngularSpeed;
	}
	if (keystate[mCounterClockwiseKey])
	{
		zangularSpeed -= mMaxAngularSpeed;
	}
	SetZAngularSpeed(zangularSpeed);
}

void InputComponent::LoadProperties(const rapidjson::Value& inObj) {
	Component::LoadProperties(inObj);

	float maxForwardSpeed;
	if (JsonHelper::GetFloat(inObj, "maxForwardSpeed", maxForwardSpeed)) {
		SetMaxForwardSpeed(maxForwardSpeed);
	}

	float maxAngularSpeed;
	if (JsonHelper::GetFloat(inObj, "maxAngularSpeed", maxAngularSpeed)) {
		SetMaxAngularSpeed(maxAngularSpeed);
	}
}
