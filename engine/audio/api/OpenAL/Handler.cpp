#include "Handler.h"

#include "System.h"

OpenAL::Handler::Handler(OpenAL::System* system, ALuint source)
    : mSystem(system), mSource(source) {}
OpenAL::Handler::~Handler() {}

bool OpenAL::Handler::IsValid() {
    auto iter = mSystem->mHandlers.find(mSource);
    if (iter != mSystem->GetHandlers().end()) {
        return true;
    }
    return false;
}

void OpenAL::Handler::Restart() {
    alSourceRewind(mSource);
    alSourcePlay(mSource);
}

// todo: フェードアウトはサポートしない．時間があったらする．
void OpenAL::Handler::Stop(bool allowedFadeOut) { alSourceStop(mSource); }

void OpenAL::Handler::SetPaused(bool pause) {
    if (pause) {
        alSourcePause(mSource);
    } else {
        alSourcePlay(mSource);
    }
}

void OpenAL::Handler::SetVolume(float volume) {
    alSourcef(mSource, AL_GAIN, volume);
}

void OpenAL::Handler::SetPitch(float value) {
    alSourcef(mSource, AL_PITCH, value);
}

// todo: 他のパラメータ用？
void OpenAL::Handler::SetParameter(const std::string& name, float value) {};

bool OpenAL::Handler::GetPaused() const {
    ALint state;
    alGetSourcei(mSource, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

float OpenAL::Handler::GetVolume() const {
    ALfloat volume;
    alGetSourcef(mSource, AL_GAIN, &volume);
    return volume;
}

float OpenAL::Handler::GetPitch() const {
    ALfloat pitch;
    alGetSourcef(mSource, AL_PITCH, &pitch);
    return pitch;
}

// todo: 他のパラメータ用？
float OpenAL::Handler::GetParameter(const std::string& name) { return 0.0; }
