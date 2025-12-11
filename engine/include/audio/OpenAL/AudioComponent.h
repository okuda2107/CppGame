#pragma once
#include <unordered_map>
#include <vector>

#include "SoundHandler.h"
#include "audio/AudioComponentBase.h"

namespace OpenAL {
class AudioComponent : public AudioComponentBase<class System> {
    // ハンドラはAudioSystemでnewされたものを受け取るが，deleteはこちらの責務
    std::unordered_map<std::string, class SoundHandler> mEvents2D;
    std::unordered_map<std::string, class SoundHandler> mEvents3D;

   public:
    AudioComponent(Actor* owner, class System* system);
    ~AudioComponent();

    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;

    SoundHandler GetEvent(const std::string& name);

    void RegisterEvent(const std::string& name);
    void StopAllEvents();

    TypeID GetType() const { return TypeID::TAudioComponent; }
};
}  // namespace OpenAL
