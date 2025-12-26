#include "game/object/ActorsSystem.h"

#include <algorithm>

#include "game/object/Actor.h"
#include "input/InputState.h"

ActorsSystem::ActorsSystem() : mUpdatingActors(false) {}

ActorsSystem::~ActorsSystem() { UnloadObjects(); }

void ActorsSystem::ProcessInput(const InputState& state) {
    mUpdatingActors = true;
    for (Actor* actor : mActors) {
        actor->ProcessInput(state);
    }
    mUpdatingActors = false;
}

void ActorsSystem::UpdateObjects(float deltatime) {
    mUpdatingActors = true;
    for (auto actor : mActors) {
        actor->Update(deltatime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors) {
        pending->ComputeWorldTransform();
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<class Actor*> deadActors;
    for (auto actor : mActors) {
        if (actor->GetState() == Actor::State::EDead) {
            deadActors.emplace_back(actor);
        }
    }
    for (auto actor : deadActors) {
        delete actor;
    }
}

void ActorsSystem::UnloadObjects() {
    while (!mActors.empty()) delete mActors.back();
}

void ActorsSystem::AddActor(Actor* actor) {
    if (mUpdatingActors) {
        mPendingActors.push_back(actor);
    } else {
        mActors.push_back(actor);
    }
}

void ActorsSystem::RemoveActor(Actor* actor) {
    auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end()) {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    iter = find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}
