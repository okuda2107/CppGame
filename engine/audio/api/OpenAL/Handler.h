#pragma once
#include "SoundHandler.h"

namespace OpenAL {
class Handler : public SoundHandler {
   public:
    Handler();
    ~Handler();

    bool IsValid();
    void Play();
    void Stop();
    void Pause();

    // Set the volume (0.0f to 1.0f)
    void SetVolume(float volume);

    bool IsPlaying() const;
};
}  // namespace OpenAL
