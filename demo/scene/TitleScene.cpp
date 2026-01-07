#include "TitleScene.h"

#include "../UI/BonfireUI.h"
#include "../UI/Title.h"
// #include "actor/Bonfire.h"
#include "game/scene/ActorFactory.h"

void TitleScene::LoadActors() {
    // タイトル
    mTitleID = mActorFactory->CreateUI<Title, BonfireUIDeps,
                                       TypeLists<RenderDB, StateManager>>();

    // Bonfire

    // player
}

void TitleScene::UnloadActors() {}

void TitleScene::TickRules() {}

std::string TitleScene::PollNextScene() { return ""; }
