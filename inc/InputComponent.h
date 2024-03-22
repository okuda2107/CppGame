#pragma once
#include "MoveComponent.h"
#include "LevelLoader.h"
#include "SDL.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* keystate);

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }

	TypeID GetType() const override {return TypeID::TInputComponent; }
	
	void LoadProperties(const rapidjson::Value& inObj) override ;

private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	const static int xRotationKey = SDL_SCANCODE_C;
	const static int xAnti = SDL_SCANCODE_Z;

	const static int mForwardKey = SDL_SCANCODE_W;
	const static int mBackKey = SDL_SCANCODE_S;

	const static int mClockwiseKey = SDL_SCANCODE_A;
	const static int mCounterClockwiseKey = SDL_SCANCODE_D;
};
