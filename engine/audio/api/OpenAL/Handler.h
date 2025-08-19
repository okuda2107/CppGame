#pragma once
#include <string>

#include "Math.h"
#include "SoundHandler.h"
#include "al.h"

namespace OpenAL {
class Handler : public SoundHandler {
    class System* mSystem;
    unsigned int mID;

    friend class System;

   public:
    Handler(class System* system, unsigned int id);
    ~Handler();

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
