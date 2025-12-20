#include "runtime/RuntimeSystem.h"

enum class RuntimeState {
    EGameplay,
    EPaused,
    EQuit,
};

bool RuntimeSystem::Initialize() {
    if (int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Failed to Initialize SDL:%s", SDL_GetError());
        return false;
    }

    mTicksCount = SDL_GetTicks();

    return true;
}

void RuntimeSystem::Shutdown() { SDL_Quit(); }

bool RuntimeSystem::IsRunning() { return mState != RuntimeState::EQuit; }

void RuntimeSystem::BeginFrame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltatime > 0.05f) {
        deltatime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();
}

void RuntimeSystem::EndFrame() {}

void RuntimeSystem::ProcessGameData(const RuntimeState& state) {
    mState = state;
}
