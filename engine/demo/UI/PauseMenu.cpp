#include "PauseMenu.h"

#include "Game.h"
#include "SDL.h"

PauseMenu::PauseMenu(Game* game) : UIScreen(game) {
    mGame->SetState(Game::EPaused);
    SetTitle("Chill time ... (Paused ...)");
}

PauseMenu::~PauseMenu() { mGame->SetState(Game::EGameplay); }

void PauseMenu::HandleKeyPress(int key) {
    UIScreen::HandleKeyPress(key);

    if (key == 'p') {
        Close();
    }
}
