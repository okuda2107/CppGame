#pragma once
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

class SoundEvent {
public:
    SoundEvent();
    ~SoundEvent();

    // Load sound data from file
    bool Load(const std::string& filePath);
    void Unload();

    // Returns true if associated FMOD event still exists
    bool IsValid();
    void Play();
    void Stop();
    void Pause();

    // Set the volume (0.0f to 1.0f)
    void SetVolume(float volume);

    bool IsPlaying() const;

private:
    // OpenAL buffer and source
    ALuint buffer;
    ALuint source;

    // Helper function to check for OpenAL errors
    bool checkALError(const std::string& errorMessage) const;
};
