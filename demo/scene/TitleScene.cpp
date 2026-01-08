#include "TitleScene.h"

#include "../UI/BonfireUI.h"
#include "../UI/Title.h"
#include "actor/Bonfire.h"
#include "game/scene/ActorQuery.h"

void TitleScene::LoadActors() {
    // タイトル
    mTitleID = mActorQuery->CreateUI<Title, BonfireUIDeps,
                                     TypeLists<RenderDB, StateManager>>();

    // Bonfire
    auto bonfireID =
        mActorQuery->CreateActor<Bonfire, BonfireDeps, TypeLists<RenderDB>>();

    // player

    auto bonfire = mActorQuery->GetActor<Bonfire>(bonfireID);
    if (bonfire) {
    }
}

void TitleScene::UnloadActors() {}

void TitleScene::TickRules() {}

std::string TitleScene::PollNextScene() { return ""; }
