#include "Title.h"

#include "SDL.h"
#include "game/StateManager.h"
#include "input/InputState.h"

Title::Title(UISystem* system, BonfireUIDeps deps) : BonfireUI(system, deps) {
    mStateManager.mState = GameState::EPause;
    SetTitle("Chillut's Fire", Color::White, 72);
}

Title::~Title() { mStateManager.mState = GameState::EGameplay; }

void Title::ProcessInput(const InputState& state) {
    auto iter = state.EventMap.find(SDL_KEYDOWN);
    if (iter == state.EventMap.end()) return;

    Close();
}
