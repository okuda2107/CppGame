#pragma once
#include "UIScreen.h"

class GameOverUI : public UIScreen {
    bool mFinished;
    class BonfireGameManager* mParent;

   public:
    GameOverUI(class Game* game);
    ~GameOverUI();

    void HandleKeyPress(int key) override;

    void SetTime(float time);

    // 処理が終わったか？
    void SetParent(class BonfireGameManager* parent) { mParent = parent; }
};
