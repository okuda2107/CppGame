#pragma once
#include <string>

#include "al.h"

namespace OpenAL {
// イベントの実体
class EventInstance {
    class Event* mEvent;
    ALuint mSource;

   public:
    EventInstance(Event* event);
    ~EventInstance();

    class Event* GetEvent() { return mEvent; }
    ALuint& GetSource() { return mSource; }
    ALint GetState() {
        ALint state;
        alGetSourcei(mSource, AL_SOURCE_STATE, &state);
        return state;
    }
};
}  // namespace OpenAL
