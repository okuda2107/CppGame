#include "game/Game.h"

#include <algorithm>

#include "UI/UISystem.h"
#include "audio/AudioSystem.h"
#include "input/InputSystem.h"
#include "object/Actor.h"
#include "object/ActorsSystem.h"
#include "renderer/Renderer.h"

Game::Game() : mTicksCount(0), mState(EGameplay) {
    mInputSystem = new InputSystem();
    mAudioSystem = new AudioSystem();
    // mPhysicsSystem = new PhysicsSystem();
    mUISystem = new UISystem();
    mRenderer = new Renderer(mUISystem);
}

Game<InputState>::Game() : mTicksCount(0), mState(EGameplay) {}

bool Game<InputState>::Initialize() {
    if (int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to Initialize SDL:%s", SDL_GetError());
        return false;
    }

    if (!mInputSystem->Initialize()) {
        SDL_Log("Failed to initialize input system");
        delete mInputSystem;
        mInputSystem = nullptr;
        return false;
    }

    if (!mRenderer->Initialize(1024.0f, 768.0f)) {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }

    if (!mAudioSystem->Initialize()) {
        SDL_Log("Failed to initialize audio system");
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

GAME_TEMPLATE

void Game<InputState>::Shutdown() {
    mActorsSystem->UnloadObjects();
    SDL_Quit();
}

void Game<InputState>::ProcessInput() {
    mActorsSystem->ProcessInput(mInputSystem->GetState());
}

float Game<InputState>::CalculateDeltatime() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltatime > 0.05f) {
        deltatime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
    return deltatime;
}

void Game<InputState>::UpdateGame(float deltatime) {
    mActorsSystem->UpdateObjects(deltatime);
}
