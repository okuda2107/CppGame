#pragma once
#include "UIScreen.h"

class GameOverUI : public UIScreen {
   public:
    GameOverUI(class Game* game);
    ~GameOverUI();

    void HandleKeyPress(int key) override;
};
