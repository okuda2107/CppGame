#include "GameScene.h"

#include "game/scene/ActorQuery.h"
#include "game/scene/SceneManager.h"

void GameScene::LoadActors() {
    // Player と Bonfire を取得
    auto playerIDContext = mSceneManagerData->at(mPlayerIDTag);
    mPlayerID = playerIDContext.actorID;
    auto bonfireIDContext = mSceneManagerData->at(mBonfireIDTag);
    mBonfireID = bonfireIDContext.actorID;
}

void GameScene::UnloadActors() {}

void GameScene::TickRules() {}

std::string GameScene::PollNextScene() {}
