#pragma once

class SoundHandler {
   public:
    SoundHandler() {};
    virtual ~SoundHandler() {};

    virtual bool IsValid() = 0;
    virtual void Play() {};
    virtual void Stop() {};
    virtual void Pause() {};

    // Set the volume (0.0f to 1.0f)
    virtual void SetVolume(float volume) {};

    virtual bool IsPlaying() const = 0;
};
