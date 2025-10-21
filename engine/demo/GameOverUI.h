#pragma once
#include "UIScreen.h"

class GameOverUI : public UIScreen {
    bool mFinished;

   public:
    GameOverUI(class Game* game);
    ~GameOverUI();

    void HandleKeyPress(int key) override;

    void SetTime(float time);

    // 処理が終わったか？
    bool GetFinished() { return mFinished; }
};
