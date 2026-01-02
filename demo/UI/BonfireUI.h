#pragma once
#include "game/UI/UIScreen.h"

struct BonfireUIDeps {
    class RenderDB& renderDB;
};

// UIScreenとChillut's FireのUI実装とを嚙合わせる前のAdapterクラス
class BonfireUI : public UIScreen {
   protected:
    class Texture* mTitle;
    Vector2 mTitlePos;

   public:
    BonfireUI(class UISystem* system, BonfireUIDeps& bud);

    void SetTitle(const std::string& text, const Vector3& color = Color::White,
                  int pointSize = 40);
};
