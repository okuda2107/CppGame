#pragma once
#include "UIScreen.h"

class Title : public UIScreen {
   public:
    Title(class Game* game);
    ~Title();

    void HandleKeyPress(int key) override;
};
