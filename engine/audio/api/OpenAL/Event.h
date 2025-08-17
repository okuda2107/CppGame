#pragma once
#include <string>

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
};
}  // namespace OpenAL
