#include "AudioSystem.h"
#include "alut.h"
#include "SDL_mixer.h"
#include "Game.h"

AudioSystem::AudioSystem(class Game* game) : mGame(game) {}
AudioSystem::~AudioSystem() {}

bool AudioSystem::Initialize() {
    if (alutInit(NULL, NULL) != AL_TRUE) {
        SDL_Log("Failed to Initialize OpenAL");
        return false;
    }
    alutGetError();

    return true;
}

void AudioSystem::test() {
    // test
    ALuint helloBuffer, helloSource;
    helloBuffer = alutCreateBufferHelloWorld(); // Bufferはsound data, Sourcesはどう鳴らすか
    alGenSources(1, &helloSource);
    //リスナー(自分)を空間座標に配置
	ALfloat ListenerPos[] = { 5.0, 0.0, 0.0 };
	alSourcefv(helloSource, AL_POSITION, ListenerPos);
    alSourcei(helloSource, AL_BUFFER, helloBuffer);
    alSourcePlay(helloSource);
}

void AudioSystem::Shutdown() {
    alutExit();
}

void AudioSystem::Update(float deltaTime) {
    test();
}
