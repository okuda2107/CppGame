#include "Title.h"

#include "Bonfire.h"
#include "BonfireGameManager.h"
#include "BonfirePlayer.h"
#include "FPSActor.h"
#include "Game.h"
#include "SDL.h"
#include "input/InputState.h"

Title::Title(UISystem* system) : UIScreen(system), mParent(nullptr) {
    SetTitle("Chillut's Fire", Color::White, 72);
}

Title::~Title() { mGame->SetState(Game::EGameplay); }

void Title::ProcessInput(const InputState& state) {
    auto iter = state.EventMap.find(SDL_KEYDOWN);
    if (iter == state.EventMap.end()) return;

    Close();
    if (!mParent) {
        SDL_Log("parent pointer is nullptr");
        return;
    }
    mParent->SetTitleFinished();
}
