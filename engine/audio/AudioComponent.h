#pragma once
#include <vector>

#include "Component.h"
#include "SoundHandler.h"

class AudioComponent : public Component {
    // ハンドラはAudioSystemでnewされたものを受け取るが，deleteはこちらの責務
    std::unordered_map<std::string, class SoundHandler*> mEvents2D;
    std::unordered_map<std::string, class SoundHandler*> mEvents3D;

   public:
    AudioComponent(Actor* owner, int updateOrder = 200);
    ~AudioComponent();

    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;

    SoundHandler* GetEvent(const std::string& name);

    void RegisterEvent(const std::string& name);
    void StopAllEvents();

    TypeID GetType() const { return TypeID::TAudioComponent; }
};
