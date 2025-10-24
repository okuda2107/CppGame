#include "WoodGenerator.h"

#include <algorithm>

#include "Actor.h"
#include "Game.h"
#include "Random.h"
#include "Wood.h"

WoodGenerator::WoodGenerator(class Game* game)
    : Actor(game), mTime(0.0f), mClock(0.0f), mIsRunning(false) {}

WoodGenerator::~WoodGenerator() {
    for (auto& wood : mWoods) {
        wood->SetState(Actor::State::EDead);
    }
}

void WoodGenerator::UpdateActor(float deltatime) {
    if (!mIsRunning) return;
    mTime += deltatime;
    mClock += deltatime;
    if (mClock > 1.0) {
        mClock = 0.0f;
        // 逆数関数的に確率が減少
        float T = 30.0f;
        float n = 2.0f;
        float prob = 1.0f / powf(1.0f + (mTime / T), n);
        if (Random::GetFloat() < prob) {
            auto wd = new Wood(GetGame(), this);
            auto fieldMin = GetGame()->GetFieldMin();
            auto fieldMax = GetGame()->GetFieldMax();
            wd->SetPosition(
                Vector3(Random::GetFloatRange(fieldMin->x, fieldMax->x),
                        Random::GetFloatRange(fieldMin->y, fieldMax->y), -50));
        }
    }
}

void WoodGenerator::AddWood(class Wood* wood) { mWoods.push_back(wood); }

void WoodGenerator::RemoveWood(class Wood* wood) {
    auto iter = std::find(mWoods.begin(), mWoods.end(), wood);
    if (iter != mWoods.end()) {
        mWoods.erase(iter);
    }
}
