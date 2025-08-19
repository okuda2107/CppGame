#pragma once
#include <string>

#include "Bank.h"
#include "Helper.h"
#include "SDL.h"
#include "System.h"
#include "al.h"

namespace OpenAL {
// イベントの実体
class EventInstance {
    class Event* mEvent;
    ALuint mSource;

   public:
    EventInstance(class Event* event) : mEvent(event) {
        mSource = AL_NONE;
        alGetError();
        alGenSources(1, &mSource);
        alSourcei(mSource, AL_BUFFER, event->GetSound());
        if (!event->mIs3D) {
            // リスナーから見て相対的な位置で再生する
            alSourcei(mSource, AL_SOURCE_RELATIVE, AL_TRUE);
            // 常にここで設定した相対座標で再生する
            ALfloat pos[] = {0, 0, 0};
            alSourcefv(mSource, AL_POSITION, pos);
        }
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            SDL_Log("Failed to create source: %s", alGetErrorString(error));
            return;
        }
    };
    ~EventInstance() { alDeleteSources(1, &mSource); };

    class Event* GetEvent() { return mEvent; }
    ALuint& GetSource() { return mSource; }
    ALint GetState() {
        ALint state;
        alGetSourcei(mSource, AL_SOURCE_STATE, &state);
        return state;
    }
};
}  // namespace OpenAL
