#include "core/Game.h"

Game::Game() : mTicksCount(0), mState(EGameplay), mDeltatime(0) {}

bool Game::Initialize() {
    if (int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to Initialize SDL:%s", SDL_GetError());
        return false;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::Shutdown() { SDL_Quit(); }
