#pragma once
#include <string>

#include "SoundEvent.h"

namespace OpenAL {
typedef std::string EventID;

class Event : public SoundEvent {
    EventID mID;
    bool mIsStream;
    bool mIsLoop;
    float mVolume;
    float mPitch;

    // Helper function to check for OpenAL errors
    bool checkALError(const std::string& errorMessage) const;

   public:
    Event();
    ~Event();
};
}  // namespace OpenAL
