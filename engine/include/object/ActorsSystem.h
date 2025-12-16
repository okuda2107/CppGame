#pragma once
#include <vector>

#include "ObjectsSystemBase.h"

// Actorの配列を保持し，それらのupdateを保証する
class ActorsSystem : public ObjectsSystemBase {
    friend class Actor;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    bool mUpdatingActors;

   public:
    ActorsSystem();

    void UnloadObjects() override;

    void UpdateObjects(float deltatime) = 0;

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
};
