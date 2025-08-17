#pragma once
#include <string>

#include "Helper.h"
#include "SDL.h"

namespace OpenAL {
class Event {
    class OpenAL::Bank* mBank;

   public:
    std::string mSoundID;
    bool mIsStream;
    bool mIsLoop;
    float mVolume;
    float mPitch;

    Event(class OpenAL::Bank* bank) : mBank(bank) {};
    ~Event() {};

    ALuint GetSound() { return mBank->GetSound(mSoundID); };

    ALuint CreateSource() {
        alGetError();
        ALuint source;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, GetSound());
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            SDL_Log("Failed to create source: %s", alGetErrorString(error));
            return AL_NONE;
        }
        return source;
    }
};
}  // namespace OpenAL
