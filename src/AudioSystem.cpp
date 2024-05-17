#include "AudioSystem.h"
#include "alut.h"
#include "SDL_mixer.h"
#include "Game.h"

AudioSystem::AudioSystem(class Game* game) : mGame(game) {}
AudioSystem::~AudioSystem() {}

bool AudioSystem::Initialize() {
    if (alutInit(NULL, NULL) != AL_TRUE) {
        SDL_Log("Failed to Initialize ALUT");
        return false;
    }
    alutGetError();
    // test
    ALuint helloBuffer, helloSource;
    helloBuffer = alutCreateBufferHelloWorld();
    alGenSources(1, &helloSource);
    alSourcei(helloSource, AL_BUFFER, helloBuffer);
    alSourcePlay(helloSource);
    alutSleep(1);

    return true;
}

void AudioSystem::Shutdown() {
    alutExit();
}

void AudioSystem::Update(float deltaTime) {

}
