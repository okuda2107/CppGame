#pragma once
#include "Actor.h"
#include "FPSComponent.h"
#include "Game.h"
#include "InputSystem.h"
#include "Mesh.h"
#include "MoveComponent.h"
#include "Renderer.h"

class KeyboardTestActor : Actor {
    MoveComponent* mc;
    FPSComponent* fc;
    float mForwardSpeed = 70;
    float mStrafeSpeed = 70;
    float mYawSpeed = 0.5;
    float mPitchSpeed = 0.5;

    const static SDL_Scancode mForwardKey = SDL_SCANCODE_W;
    const static SDL_Scancode mBackKey = SDL_SCANCODE_S;

    const static SDL_Scancode mRightKey = SDL_SCANCODE_D;
    const static SDL_Scancode mLeftKey = SDL_SCANCODE_A;

    const static SDL_Scancode mTurnKey = SDL_SCANCODE_L;
    const static SDL_Scancode mOppristeTurnKey = SDL_SCANCODE_J;

    const static SDL_Scancode mLookupKey = SDL_SCANCODE_I;
    const static SDL_Scancode mLookdownKey = SDL_SCANCODE_K;

   public:
    KeyboardTestActor(class Game* game) : Actor(game) {
        // 空間感を出すためのオブジェクト配置
        Actor* a = new Actor(GetGame());
        a->SetPosition(Vector3(100, -100, 0));
        a->SetScale(50.0);
        MeshComponent* a_mc = new MeshComponent(a);
        a_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
        Actor* b = new Actor(GetGame());
        b->SetPosition(Vector3(100, 100, 0));
        MeshComponent* b_mc = new MeshComponent(b);
        b_mc->SetMesh(
            GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));

        fc = new FPSComponent(this);
        fc->SetMaxPitch(Math::Pi / 4);
        mc = new MoveComponent(this);
    }

    void ActorInput(const class InputState& state) override {
        float fowardSpeed = 0.0f;
        if (state.Keyboard.GetKeyValue(mForwardKey))
            fowardSpeed += mForwardSpeed;
        if (state.Keyboard.GetKeyValue(mBackKey)) fowardSpeed -= mForwardSpeed;
        mc->SetForwardSpeed(fowardSpeed);

        float rightSpeed = 0.0f;
        if (state.Keyboard.GetKeyValue(mRightKey)) rightSpeed += mStrafeSpeed;
        if (state.Keyboard.GetKeyValue(mLeftKey)) rightSpeed -= mStrafeSpeed;
        mc->SetRightSpeed(rightSpeed);

        float yawSpeed = 0.0f;
        if (state.Keyboard.GetKeyValue(mTurnKey)) yawSpeed += mYawSpeed;
        if (state.Keyboard.GetKeyValue(mOppristeTurnKey)) yawSpeed -= mYawSpeed;
        mc->SetYawSpeed(yawSpeed);

        float pitchSpeed = 0.0f;
        if (state.Keyboard.GetKeyValue(mLookupKey)) pitchSpeed -= mPitchSpeed;
        if (state.Keyboard.GetKeyValue(mLookdownKey)) pitchSpeed += mPitchSpeed;
        fc->SetPitchSpeed(pitchSpeed);
    }
};
