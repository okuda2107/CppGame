#pragma once
#include <vector>

#include "base/ObjectsSystemBase.h"

// Actorの配列を保持し，それらのupdateを保証する
class ActorsSystem : public ObjectsSystemBase<class InputState> {
    friend class Actor;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    bool mUpdatingActors;

   public:
    ActorsSystem();

    void UnloadObjects() override;

    void ProcessInput(const InputState& state);
    void UpdateObjects(float deltatime);

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
};
