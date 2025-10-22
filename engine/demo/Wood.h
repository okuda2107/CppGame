#pragma once

#include "Actor.h"

class Wood : public Actor {
    float mTime;
    class WoodGenerator* mParent;

   public:
    Wood(class Game* game, class WoodGenerator* parent);
    ~Wood();

    void UpdateActor(float deltatime) override;
};
