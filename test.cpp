#include "SDL_mixer.h"
#include "SDL.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) <  0) {}
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        SDL_Log("failed to initialize audiosystem");
        return 1;
    }
    Mix_Music* music;
    music = Mix_LoadMUS("Asset/mac.mp3");
    if  (music == NULL) {
        return 1;
    }
    Mix_PlayMusic(music, -1);
    for (int i = 0; i < 1000000; i++) {}
    Mix_PauseMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    return 0;
}
