#include "AudioSystem.h"

#include "Game.h"
#include "SDL_mixer.h"
#include "al.h"
#include "alc.h"
#include "alext.h"
#include "alut.h"
#include "efx-creative.h"
#include "efx-presets.h"
#include "efx.h"

AudioSystem::AudioSystem(class Game* game) : mGame(game) {}
AudioSystem::~AudioSystem() {}

void AudioSystem::test() {
    // test
    ALuint helloBuffer, helloSource;
    helloBuffer = alutCreateBufferHelloWorld();  // Bufferはsound data,
                                                 // Sourcesはどう鳴らすか
    alGenSources(1, &helloSource);
    // リスナー(自分)を空間座標に配置
    ALfloat ListenerPos[] = {5.0, 0.0, 0.0};
    alSourcefv(helloSource, AL_POSITION, ListenerPos);
    alSourcei(helloSource, AL_BUFFER, helloBuffer);
    alSourcePlay(helloSource);
    alGenEffects(1, &effect);
}
