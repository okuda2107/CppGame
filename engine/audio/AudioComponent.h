#pragma once
#include <vector>

#include "Component.h"
#include "SoundEvent.h"

class AudioComponent : public Component {
    std::vector<SoundEvent> mEvents2D;
    std::vector<SoundEvent> mEvents3D;

   public:
    AudioComponent(Actor* owner, int updateOrder = 200);
    ~AudioComponent();

    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;

    SoundEvent PlayEvent(const std::string& name);
    void StopAllEvents();
};
