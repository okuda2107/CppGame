#include "TitleScene.h"

#include "UI/BonfireUI.h"
#include "UI/Title.h"
#include "actor/Bonfire.h"

void TitleScene::LoadActors() {
    // タイトル
    {
        auto deps = BonfireUIDeps{mRenderDB, mStateManager};
        auto title = new Title(&mUISystem, deps);
        mTitleID = title->GetID();
    }

    // Bonfire
    {
        auto deps = BonfireDeps{mRenderDB};
        auto bonfire = new Bonfire(&mActorsSystem, deps);
    }

    // player
}
