#pragma once
#include "AudioSystem.h"

// Actorに付与されて，再生，停止やポジショナルな情報などを伝達する役割
class SoundHandler {
    friend class AudioSystem;

   protected:
    SoundHandler() {};

   public:
    virtual ~SoundHandler() {};
    virtual bool IsValid() = 0;
    virtual void Restart() = 0;
    virtual void Stop(bool allowedFadeOut = true) = 0;

    virtual void SetPaused(bool pause) = 0;
    // Set the volume (0.0f to 1.0f)
    virtual void SetVolume(float volume) = 0;
    virtual void SetPitch(float value) = 0;
    virtual void SetParameter(const std::string& name, float value) = 0;

    virtual bool GetPaused() const = 0;
    virtual float GetVolume() const = 0;
    virtual float GetPitch() const = 0;
    virtual float GetParameter(const std::string& name) = 0;

    virtual bool Is3D() const = 0;
    virtual void Set3DAttributes(const Matrix4& worldTrans) = 0;
};
