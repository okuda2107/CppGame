#pragma once
#include <vector>

#include "Component.h"
#include "SoundHandler.h"

class AudioComponent : public Component {
    // ハンドラはAudioSystemでnewされたものを受け取るが，deleteはこちらの責務
    std::vector<class SoundHandler*> mEvents2D;
    std::vector<class SoundHandler*> mEvents3D;

   public:
    AudioComponent(Actor* owner, int updateOrder = 200);
    ~AudioComponent();

    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;

    SoundHandler* PlayEvent(const std::string& name);
    void StopAllEvents();
};
