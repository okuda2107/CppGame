#pragma once
#include "game/UI/UIScreen.h"

// UIScreenとChillut's FireのUI実装とを嚙合わせる前のAdapterクラス
class BonfireUI : public UIScreen {
   public:
    BonfireUI(class UISystem* system) : UIScreen(system) { mFont = SetFont() }

    void SetTitle(std::string& text) {}
};
