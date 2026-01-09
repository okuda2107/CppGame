#pragma once

#include "game/object/Actor.h"

class WoodGenerator : public Actor {
    float mTime;
    float mClock;
    bool mIsRunning;
    std::vector<class Wood*> mWoods;

    class ActorsSystem& mActorsSystem;

   public:
    WoodGenerator(class ActorsSystem* system);
    ~WoodGenerator();

    void UpdateActor(float deltatime) override;

    std::vector<class Wood*>& GetWoods() { return mWoods; }

    void AddWood(class Wood* wood);
    void RemoveWood(class Wood* wood);

    void SetRunning() { mIsRunning = true; }
};
