#include "GameOverUI.h"

#include <sstream>

#include "Bonfire.h"
#include "BonfireGameManager.h"
#include "FPSActor.h"
#include "Game.h"
#include "SDL.h"

GameOverUI::GameOverUI(Game* game) : UIScreen(game), mParent(nullptr) {
    mGame->SetState(Game::EPaused);
    SetTitle("Chillut's Fire", Color::White, 72);
}

GameOverUI::~GameOverUI() {
    // この直後Titleがロードされるため，EGamePlayにする必要はない
    // mGame->SetState(Game::EGameplay);
}

void GameOverUI::SetTime(float time) {
    std::stringstream ss;
    ss << "Time: " << time;
    SetTitle(ss.str(), Color::White, 72);
}

void GameOverUI::HandleKeyPress(int key) {
    UIScreen::HandleKeyPress(key);

    if (key) {
        Close();
        if (!mParent) {
            SDL_Log("parent pointer is nullptr");
            return;
        }
        mParent->SetResultFinished();
    }
}
