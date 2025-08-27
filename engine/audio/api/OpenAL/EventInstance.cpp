#include "EventInstance.h"

#include "Event.h"
#include "Helper.h"
#include "SDL.h"

OpenAL::EventInstance::EventInstance(class Event* event) : mEvent(event) {
    event->AddInstance(this);
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
}

OpenAL::EventInstance::~EventInstance() {
    mEvent->RemoveInstance(this);
    alSourcei(mSource, AL_BUFFER, 0);
    alDeleteSources(1, &mSource);
}
