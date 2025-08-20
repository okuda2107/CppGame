#pragma once
#include <algorithm>
#include <string>
#include <vector>

#include "Bank.h"
#include "SDL.h"

namespace OpenAL {
// イベントで再生するサウンドのパラメータを保持
class Event {
    class Bank* mBank;
    std::vector<class EventInstance*> mInstances;

   public:
    std::string mSoundID;
    bool mIs3D;
    bool mIsStream;
    bool mIsLoop;
    float mVolume;
    float mPitch;

    Event(class Bank* bank);
    ~Event();

    ALuint GetSound() { return mBank->GetSound(mSoundID); };

    void AddInstance(class EventInstance* instance);
    void RemoveInstance(class EventInstance* instance);
};
}  // namespace OpenAL
