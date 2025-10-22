#pragma once

#include "UIScreen.h"
#include "Utility/Coroutine.h"

class AlreadyHaveWoodUI : public UIScreen {
    Coroutine* mCoroutine;
    float endTime;

   public:
    AlreadyHaveWoodUI(class Game* game) : UIScreen(game) {
        mCoroutine = new Coroutine();
        endTime = mCoroutine->AddCoroutine(1.0f, [](float t) {});
        SetTitle("already have it ...");
    }
    ~AlreadyHaveWoodUI() { delete mCoroutine; }

    void Update(float deltatime) {
        mCoroutine->Update(deltatime);
        if (mCoroutine->CheckCoroutine(endTime)) {
            Close();
        }
    }

    void Draw(Shader* shader) {
        mTitlePos = Vector2(0.0f, 200.0f);
        UIScreen::Draw(shader);
    }
};
