#pragma once
#include "UIScreen.h"

class Title : public UIScreen {
    bool mFinished;
    class BonfireGameManager* mParent;

   public:
    Title(class Game* game);
    ~Title();

    void HandleKeyPress(int key) override;

    // Closingするときに処理を伝えたいため保持
    void SetParent(class BonfireGameManager* parent) { mParent = parent; }
};
