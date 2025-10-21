#pragma once
#include "Actor.h"

class Bonfire : public Actor {
    float mTime;
    bool mFinished;

   public:
    Bonfire(class Game* game);

    float GetTime() { return mTime; }
    bool GetFinished() { return mFinished; }
};
