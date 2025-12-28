#include "game/object/ActorsSystem.h"

#include <algorithm>

#include "game/object/Actor.h"
#include "input/InputState.h"

ActorsSystem::ActorsSystem() : mUpdatingActors(false) {}

ActorsSystem::~ActorsSystem() {
    UnloadObjects();
    for (auto& [key, exe] : mExecution) {
        delete exe->input;
        delete exe->update;
        delete exe;
    }
    mExecution.clear();
}

void ActorsSystem::ProcessInput(const InputState& state) {
    mUpdatingActors = true;
    for (auto [key, actors] : mActors) {
        for (Actor* actor : actors) {
            auto iter = mExecution.find(key);
            if (iter != mExecution.end())
                (*iter->second->input)(actor, state);
            else
                actor->ProcessInput(state);
        }
    }
    mUpdatingActors = false;
}

void ActorsSystem::UpdateObjects(float deltatime) {
    mUpdatingActors = true;
    for (auto [key, actors] : mActors) {
        for (Actor* actor : actors) {
            auto iter = mExecution.find(key);
            if (iter != mExecution.end())
                (*iter->second->update)(actor, deltatime);
            else
                actor->Update(deltatime);
        }
    }
    mUpdatingActors = false;

    for (auto [key, pendings] : mPendingActors) {
        for (Actor* pending : pendings) {
            pending->ComputeWorldTransform();
            mActors[key].emplace_back(pending);
        }
    }
    mPendingActors.clear();

    std::vector<class Actor*> deadActors;
    for (auto [key, actors] : mActors) {
        for (auto actor : actors) {
            if (actor->GetState() == Actor::State::EDead) {
                deadActors.emplace_back(actor);
            }
        }
    }
    for (auto actor : deadActors) {
        delete actor;
    }
}

void ActorsSystem::UnloadObjects() {
    for (auto [key, actors] : mActors)
        while (!actors.empty()) delete actors.back();
}

void ActorsSystem::AddActor(const std::string& tag, Actor* actor) {
    if (mUpdatingActors) {
        auto iter = mPendingActors.find(tag);
        if (iter != mPendingActors.end())
            iter->second.push_back(actor);
        else {
            mPendingActors[tag] = std::vector<Actor*>();
            mPendingActors[tag].push_back(actor);
        }
    } else {
        auto iter = mActors.find(tag);
        if (iter != mActors.end())
            iter->second.push_back(actor);
        else {
            mActors[tag] = std::vector<Actor*>();
            mActors[tag].push_back(actor);
        }
    }
}

void ActorsSystem::RemoveActor(const std::string& tag, Actor* actor) {
    auto mapIter = mPendingActors.find(tag);
    if (mapIter != mPendingActors.end()) {
        auto iter = find(mapIter->second.begin(), mapIter->second.end(), actor);
        if (iter != mapIter->second.end()) {
            std::iter_swap(iter, mapIter->second.end() - 1);
            mapIter->second.pop_back();
            return;
        }
    }
    mapIter = mActors.find(tag);
    if (mapIter != mActors.end()) {
        auto iter = find(mapIter->second.begin(), mapIter->second.end(), actor);
        if (iter != mapIter->second.end()) {
            std::iter_swap(iter, mapIter->second.end() - 1);
            mapIter->second.pop_back();
            return;
        }
    }
}
