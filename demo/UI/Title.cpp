#include "Title.h"

#include "Bonfire.h"
#include "BonfireGameManager.h"
#include "BonfirePlayer.h"
#include "FPSActor.h"
#include "Game.h"
#include "SDL.h"

Title::Title(UISystem* system) : UIScreen(system), mParent(nullptr) {
    mGame->SetState(Game::EPaused);
    SetTitle("Chillut's Fire", Color::White, 72);
}

Title::~Title() { mGame->SetState(Game::EGameplay); }

void Title::HandleKeyPress(int key) {
    UIScreen::HandleKeyPress(key);

    if (key) {
        Close();
        if (!mParent) {
            SDL_Log("parent pointer is nullptr");
            return;
        }
        mParent->SetTitleFinished();
    }
}
