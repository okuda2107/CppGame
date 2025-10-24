#pragma once

#include <Actor.h>

class WoodGenerator : public Actor {
    float mTime;
    float mClock;
    bool mIsRunning;
    std::vector<class Wood*> mWoods;

   public:
    WoodGenerator(class Game* game);
    ~WoodGenerator();

    void UpdateActor(float deltatime) override;

    std::vector<class Wood*>& GetWoods() { return mWoods; }

    void AddWood(class Wood* wood);
    void RemoveWood(class Wood* wood);

    void SetRunning() { mIsRunning = true; }
};
