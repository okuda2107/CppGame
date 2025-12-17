#include "core/Game.h"

#include <algorithm>

#include "input/InputSystem.h"
#include "object/Actor.h"
#include "object/ActorsSystem.h"

Game::Game() : mTicksCount(0), mState(EGameplay) {}

bool Game::Initialize() {
    if (int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to Initialize SDL:%s", SDL_GetError());
        return false;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::Shutdown() {
    mActorsSystem->UnloadObjects();
    SDL_Quit();
}

void Game::ProcessInput() {
    mActorsSystem->ProcessInput(mInputSystem->GetState());
}

float Game::CalculateDeltatime() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltatime > 0.05f) {
        deltatime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
    return deltatime;
}

void Game::UpdateGame(float deltatime) {
    mActorsSystem->UpdateObjects(deltatime);
}
