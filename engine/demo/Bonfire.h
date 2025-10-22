#pragma once
#include "Actor.h"

class Bonfire : public Actor {
    float mTime;
    float mLimit;
    bool mFinished;

    const float cMaxLimit = 5.0f;

   public:
    Bonfire(class Game* game);

    void UpdateActor(float deltatime) override;

    void Initialize();

    float GetTime() { return mTime; }
    bool GetFinished() { return mFinished; }
};
