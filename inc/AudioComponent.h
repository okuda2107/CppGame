#pragma once
#include "Component.h"
#include "SoundEvent.h"
#include <vector>

class AudioComponent : public Component {
    public:
    AudioComponent(Actor* owner, int updateOrder = 200);
    ~AudioComponent();

    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;

    SoundEvent PlayEvent(const std::string& name);
    void StopAllEvents();

    private:
    std::vector<SoundEvent> mEvent2D;
    std::vector<SoundEvent> mEvents3D;

};
