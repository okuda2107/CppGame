#include "audio/OpenAL/AudioComponent.h"

#include "audio/AudioComponentBase.h"
#include "audio/OpenAL/SoundHandler.h"
#include "audio/OpenAL/System.h"
#include "core/Actor.h"
#include "core/Game.h"

OpenAL::AudioComponent::AudioComponent(Actor* owner, System* system)
    : AudioComponentBase(owner, system) {}

OpenAL::AudioComponent::~AudioComponent() { StopAllEvents(); }

void OpenAL::AudioComponent::Update(float deltaTime) {
    Component::Update(deltaTime);

    // Remove invalid 2D events
    auto iter = mEvents2D.begin();
    while (iter != mEvents2D.end()) {
        if (!iter->second.IsValid()) {
            iter = mEvents2D.erase(iter);
        } else {
            ++iter;
        }
    }

    // Remove invalid 3D events
    iter = mEvents3D.begin();
    while (iter != mEvents3D.end()) {
        if (!iter->second.IsValid()) {
            iter = mEvents3D.erase(iter);
        } else {
            ++iter;
        }
    }
}

void OpenAL::AudioComponent::OnUpdateWorldTransform() {
    // Update 3D event's world transforms
    Matrix4 world = mOwner->GetWorldTransform();
    for (auto event : mEvents3D) {
        if (event.second.IsValid()) {
            event.second.Set3DAttributes(world);
        }
    }
}

//
OpenAL::SoundHandler OpenAL::AudioComponent::GetEvent(const std::string& name) {
    auto iter3D = mEvents3D.find(name);
    if (iter3D != mEvents3D.end() && iter3D->second.IsValid())
        return iter3D->second;
    auto iter2D = mEvents2D.find(name);
    if (iter2D != mEvents2D.end() && iter2D->second.IsValid())
        return iter2D->second;
    return OpenAL::SoundHandler(mSystem, 0);
}

// AudioSystemに要請して，イベントを再生する準備をする．
void OpenAL::AudioComponent::RegisterEvent(const std::string& name) {
    // ここでSoundHandlerがnewされる．
    SoundHandler e = mSystem->PlayEvent(name);
    if (!e.IsValid()) return;
    // Is this 2D or 3D?
    if (e.Is3D()) {
        mEvents3D.emplace(name, e);
        // Set initial 3D attributes
        e.Set3DAttributes(mOwner->GetWorldTransform());
    } else {
        mEvents2D.emplace(name, e);
    }
}

void OpenAL::AudioComponent::StopAllEvents() {
    // Stop all sounds
    for (auto& e : mEvents2D) {
        e.second.Stop();
    }
    for (auto& e : mEvents3D) {
        e.second.Stop();
    }
    mEvents2D.clear();
    mEvents3D.clear();
}
