#pragma once
#include "Component.h"
#include "Math.h"
#include "document.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltatime);

	void SetXAngularSpeed(float angSpeed) { mXAngularSpeed = angSpeed; }
	void SetYAngularSpeed(float angSpeed) { mYAngularSpeed = angSpeed; }
	void SetZAngularSpeed(float angSpeed) { mZAngularSpeed = angSpeed; }
	void SetForwardSpeed(float forwSpeed) { mForwardSpeed = forwSpeed; }

	TypeID GetType() const { return TypeID::TMoveComponent; }

	void LoadProperties(const rapidjson::Value& inObj) override;
private:
	float mXAngularSpeed;
	float mYAngularSpeed;
	float mZAngularSpeed;
	float mForwardSpeed;
};
