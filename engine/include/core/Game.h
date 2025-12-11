#pragma once
#include <vector>

#include "SDL.h"

class Game {
    Uint32 mTicksCount;
    float mDeltatime;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

   public:
    bool Initialize();
    void Shutdown();

    // ゲームループのフラグ
    bool IsGameLoop();

    void UpdateActors();

    float GetDeltatime() { return mDeltatime; }

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
};
