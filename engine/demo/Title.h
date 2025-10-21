#pragma once
#include "UIScreen.h"

class Title : public UIScreen {
    bool mFinished;

   public:
    Title(class Game* game);
    ~Title();

    void HandleKeyPress(int key) override;

    // 処理が終わったか？
    bool GetFinished() { return mFinished; }
};
