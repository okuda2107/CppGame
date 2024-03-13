#include "AudioSYstem.h"
#include "SDL_mixer.h"
#include "Game.h"

AudioSystem::AudioSystem(class Game* game) : mGame(game) {}

bool AudioSystem::Initialize() {
    if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        2,
        1024
    ) != 0) {
        SDL_Log("Failed to open Audio");
        return false;
    }
    return true;
}

void AudioSystem::LoadAudio() {

}
