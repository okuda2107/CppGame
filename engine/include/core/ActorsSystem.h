#pragma once
#include <vector>

// Actorの配列を保持し，それらのupdateを保証する
class ActorsSystem {
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    bool mUpdatingActors;

   public:
    ActorsSystem();

    void UnloadActors();

    void UpdateActors(float deltatime);

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
};
