#pragma once
#include "game/UI/UIScreen.h"

class Title : public UIScreen {
    class BonfireGameManager* mParent;

   public:
    Title(class UISystem* system);
    ~Title();

    void ProcessInput(const class InputState& state) override;

    // Closingするときに処理を伝えたいため保持
    void SetParent(class BonfireGameManager* parent) { mParent = parent; }
};
