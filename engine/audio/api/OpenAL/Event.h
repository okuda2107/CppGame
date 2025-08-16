#pragma once
#include <string>

namespace OpenAL {
class Event {
   public:
    std::string mSoundID;
    bool mIsStream;
    bool mIsLoop;
    float mVolume;
    float mPitch;

    Event() {};
    ~Event() {};

    // Helper function to check for OpenAL errors
    bool checkALError(const std::string& errorMessage) const;
};
}  // namespace OpenAL
