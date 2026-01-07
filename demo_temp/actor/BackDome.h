#pragma once
#include "Actor.h"

class BackDome : public Actor {
    float mTime;
    class SkydomeComponent* sc;

   public:
    BackDome(class Game* game);

    void UpdateActor(float deltatime) override;
};
