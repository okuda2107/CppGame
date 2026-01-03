#include "Title.h"

#include "SDL.h"
#include "input/InputState.h"
#include "scene/TitleScene.h"

Title::Title(UISystem* system, BonfireUIDeps& deps) : BonfireUI(system, deps) {
    SetTitle("Chillut's Fire", Color::White, 72);
}

Title::~Title() { mGame->SetState(Game::EGameplay); }

void Title::ProcessInput(const InputState& state) {
    auto iter = state.EventMap.find(SDL_KEYDOWN);
    if (iter == state.EventMap.end()) return;

    Close();
}
