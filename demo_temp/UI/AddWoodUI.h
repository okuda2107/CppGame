#pragma once

#include "game/UI/UIScreen.h"

class AddWoodUI : public UIScreen {
   public:
    AddWoodUI(class UISystem* system) : UIScreen(system) {
        SetTitle("Add wood ... [e]");
    }

    void Draw(Shader* shader) {
        mTitlePos = Vector2(200.0f, 300.0f);
        UIScreen::Draw(shader);
    }
};
