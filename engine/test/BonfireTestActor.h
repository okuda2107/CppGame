#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "FPSComponent.h"
#include "Game.h"
#include "InputSystem.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "SkydomeTestActor.h"

class BonfireTestActor : Actor {
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
    BonfireTestActor(class Game* game) : Actor(game) {
        // skybox
        new SkydomeTestActor(game);
        // たき火仮配置
        Actor* a = new Actor(GetGame());
        a->SetPosition(Vector3(100, -100, -50));
        a->SetScale(30.0);
        RenderConfig config;
        config.mBlend = false;
        config.mCullFaceBack = false;
        config.mDepthMask = true;
        config.mDepthTest = true;
        MeshComponent* a_mc = new MeshComponent(a, &config);
        a_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
        AudioComponent* a_ac = new AudioComponent(a);
        a_ac->RegisterEvent("takibi");
        SoundHandler* e = a_ac->GetEvent("takibi");
        if (!e) {
            std::cerr << "failed to get sound event" << std::endl;
        } else {
            e->Restart();
        }

        // 床配置
        Actor* b = new Actor(game);
        b->SetScale(10.0f);
        b->SetPosition(Vector3(0, 0, -70));

        MeshComponent* b_mc = new MeshComponent(b, &config);
        b_mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));

        // 環境光
        game->GetRenderer()->SetAmbientLight(Vector3(0.1, 0.1, 0.2));

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
