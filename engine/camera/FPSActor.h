#pragma once
#include "Actor.h"
#include "FPSComponent.h"
#include "SDL.h"

//  キーマウでの操作ができるFPS視点のActor
class FPSActor : public Actor {
    class MoveComponent* mMoveComp;
    class AudioComponent* mAudioComp;
    class FPSComponent* mFPSComp;
    class SoundHandler* mFootstep;
    float mLastFootstep;

    float mForwardSpeed;
    float mStrafeSpeed;

    const int mMaxMouseSpeed = 500;
    const float mMaxAngularSpeed = Math::Pi * 8;

    const static SDL_Scancode mForwardKey = SDL_SCANCODE_W;
    const static SDL_Scancode mBackKey = SDL_SCANCODE_S;

    const static SDL_Scancode mRightKey = SDL_SCANCODE_D;
    const static SDL_Scancode mLeftKey = SDL_SCANCODE_A;

   public:
    FPSActor(class Game* game);

    void ActorInput(const InputState& state) override;
    void UpdateActor(float deltaTime) override;

    void SetForwardSpeed(float forwardSpeed) { mForwardSpeed = forwardSpeed; }
    void SetStrafeSpeed(float strafeSpeed) { mStrafeSpeed = strafeSpeed; }
    void SetPitchAngular(float pitchAngular) {
        mFPSComp->SetPitch(pitchAngular);
    }
};
