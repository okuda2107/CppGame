#include "AudioComponent.h"

#include "Actor.h"
#include "Game.h"
#include "SoundHandler.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {}

AudioComponent::~AudioComponent() { StopAllEvents(); }

void AudioComponent::Update(float deltaTime) {
    Component::Update(deltaTime);

    // Remove invalid 2D events
    auto iter = mEvents2D.begin();
    while (iter != mEvents2D.end()) {
        if (!iter->second->IsValid()) {
            delete iter->second;
            iter = mEvents2D.erase(iter);
        } else {
            ++iter;
        }
    }

    // Remove invalid 3D events
    iter = mEvents3D.begin();
    while (iter != mEvents3D.end()) {
        if (!iter->second->IsValid()) {
            delete iter->second;
            iter = mEvents3D.erase(iter);
        } else {
            ++iter;
        }
    }
}

void AudioComponent::OnUpdateWorldTransform() {
    // Update 3D event's world transforms
    Matrix4 world = mOwner->GetWorldTransform();
    for (auto event : mEvents3D) {
        if (event.second->IsValid()) {
            event.second->Set3DAttributes(world);
        }
    }
}

//
SoundHandler* AudioComponent::GetEvent(const std::string& name) {
    auto iter3D = mEvents3D.find(name);
    if (iter3D != mEvents3D.end() && iter3D->second->IsValid())
        return iter3D->second;
    auto iter2D = mEvents2D.find(name);
    if (iter2D != mEvents2D.end() && iter2D->second->IsValid())
        return iter2D->second;
    return nullptr;
}

// AudioSystemに要請して，イベントを再生する準備をする．
void AudioComponent::RegisterEvent(const std::string& name) {
    // ここでSoundHandlerがnewされる．
    SoundHandler* e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
    // Is this 2D or 3D?
    if (e->Is3D()) {
        mEvents3D.emplace(name, e);
        // Set initial 3D attributes
        e->Set3DAttributes(mOwner->GetWorldTransform());
    } else {
        mEvents2D.emplace(name, e);
    }
}

void AudioComponent::StopAllEvents() {
    // Stop all sounds
    for (auto& e : mEvents2D) {
        e.second->Stop();
        delete e.second;
    }
    for (auto& e : mEvents3D) {
        e.second->Stop();
        delete e.second;
    }
    mEvents2D.clear();
    mEvents3D.clear();
}
