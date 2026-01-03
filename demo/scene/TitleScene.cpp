#include "TitleScene.h"

#include "UI/BonfireUI.h"
#include "UI/Title.h"

void TitleScene::LoadActors() {
    // タイトル
    auto deps = BonfireUIDeps{mRenderDB, mStateManager};
    auto title = new Title(&mUISystem, deps);
    mTitleID = title->GetID();

    // player
}
