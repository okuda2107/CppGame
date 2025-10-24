#include "WoodGenerator.h"

#include <algorithm>

#include "Actor.h"
#include "Random.h"
#include "Wood.h"

WoodGenerator::WoodGenerator(class Game* game)
    : Actor(game), mTime(0.0f), mIsRunning(false) {}

WoodGenerator::~WoodGenerator() {
    for (auto& wood : mWoods) {
        wood->SetState(Actor::State::EDead);
    }
}

void WoodGenerator::UpdateActor(float deltatime) {
    if (!mIsRunning) return;
    mTime += deltatime;
    if (mTime > 5.0) {
        mTime = 0.0f;
        // 50%の確率で木を生成
        if (Random::GetFloat() < 0.5) {
            auto wd = new Wood(GetGame(), this);
            wd->SetPosition(Vector3(-Random::GetFloatRange(-500, 2500),
                                    Random::GetFloatRange(-500, 2500), -50));
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
