#pragma once

#include "UIScreen.h"

class HaveWoodUI : public UIScreen {
   public:
    HaveWoodUI(class Game* game) : UIScreen(game) {
        SetTitle("pick up wood by press e ...");
    }

    void Draw(Shader* shader) {
        mTitlePos = Vector2(100.0f, 300.0f);
        UIScreen::Draw(shader);
    }
};
