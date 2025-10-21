#include "GameOverUI.h"

#include <sstream>

#include "Bonfire.h"
#include "FPSActor.h"
#include "Game.h"
#include "SDL.h"

GameOverUI::GameOverUI(Game* game) : UIScreen(game), mFinished(false) {
    mGame->SetState(Game::EPaused);
    SetTitle("Chillut's Fire", Color::White, 72);
}

GameOverUI::~GameOverUI() { mGame->SetState(Game::EGameplay); }

void GameOverUI::SetTime(float time) {
    std::stringstream ss;
    ss << "Time: " << time;
    SetTitle(ss.str(), Color::White, 72);
}

void GameOverUI::HandleKeyPress(int key) {
    UIScreen::HandleKeyPress(key);

    if (key) {
        // フラグを立てて，managerの命令を待つ
        mFinished = true;
    }
}
