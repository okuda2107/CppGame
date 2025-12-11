#pragma once
#include <string>

#include "AL/al.h"
#include "core/Math.h"

namespace OpenAL {
class SoundHandler {
    friend class System;

   public:
    class System* mSystem;
    unsigned int mID;
    SoundHandler(class System* system, unsigned int id);
    ~SoundHandler();

    bool IsValid();
    void Restart();
    void Stop(bool allowedFadeOut = true);

    void SetPaused(bool pause);
    // Set the volume (0.0f to 1.0f)
    void SetVolume(float volume);
    void SetPitch(float value);
    void SetParameter(const std::string& name, float value);

    bool GetPaused() const;
    float GetVolume() const;
    float GetPitch() const;
    float GetParameter(const std::string& name);

    bool Is3D() const;
    void Set3DAttributes(const Matrix4& worldTrans);
};
}  // namespace OpenAL
