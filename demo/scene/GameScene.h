#pragma once
#include "BonfireSceneBase.h"
#include "game/object/Actor.h"

class GameScene : public BonfireSceneBase {
    ActorID mPlayerID;
    ActorID mBonfireID;

   public:
    void LoadActors();
    void UnloadActors();

    void TickRules();

    std::string PollNextScene();
};
