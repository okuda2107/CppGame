#pragma once
#include "AudioSystem.h"

class SoundHandler {
   protected:
    friend class AudioSystem;
    SoundHandler() {};
    virtual ~SoundHandler() {};

   public:
    virtual bool IsValid() { return false; };
    virtual void Restart() {};
    virtual void Stop(bool allowedFadeOut = true) {};

    virtual void SetPaused(bool pause) {};
    // Set the volume (0.0f to 1.0f)
    virtual void SetVolume(float volume) {};
    virtual void SetPitch(float value) {};
    virtual void SetParameter(const std::string& name, float value) {};

    virtual bool GetPaused() const { return false; };
    virtual float GetVolume() const { return 0.0; };
    virtual float GetPitch() const { return 0.0; };
    virtual float GetParameter(const std::string& name) { return 0.0; };

    virtual bool Is3D() const { return false; };
    virtual void Set3DAttributes(const Matrix4& worldTrans) {};
};
