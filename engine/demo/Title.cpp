#include "Title.h"

#include "Bonfire.h"
#include "FPSActor.h"
#include "Game.h"
#include "SDL.h"

Title::Title(Game* game) : UIScreen(game), mFinished(false) {
    mGame->SetState(Game::EPaused);
    SetTitle("Chillut's Fire", Color::White, 72);
}

Title::~Title() { mGame->SetState(Game::EGameplay); }

void Title::HandleKeyPress(int key) {
    UIScreen::HandleKeyPress(key);

    if (key) {
        // フラグを立てて，managerの命令を待つ
        mFinished = true;
    }
}
