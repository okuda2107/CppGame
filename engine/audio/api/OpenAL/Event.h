#pragma once
#include <string>

#include "Helper.h"
#include "SDL.h"
#include "api/OpenAL/Bank.h"

namespace OpenAL {
// イベントで再生するサウンドのパラメータを保持
class Event {
    class Bank* mBank;

   public:
    std::string mSoundID;
    bool mIs3D;
    bool mIsStream;
    bool mIsLoop;
    float mVolume;
    float mPitch;

    Event(class Bank* bank) : mBank(bank) {};
    ~Event() {};

    ALuint GetSound() { return mBank->GetSound(mSoundID); };

    ALuint CreateSource() {
        alGetError();
        ALuint source;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, GetSound());
        if (!mIs3D) {
            // リスナーから見て相対的な位置で再生する
            alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
            // 常にここで設定した相対座標で再生する
            ALfloat pos[] = {0, 0, 0};
            alSourcefv(source, AL_POSITION, pos);
        }
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            SDL_Log("Failed to create source: %s", alGetErrorString(error));
            return AL_NONE;
        }
        return source;
    }
};
}  // namespace OpenAL
