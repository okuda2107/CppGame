#include "TitleScene.h"

#include "BonfireSceneTag.h"
#include "UI/BonfireUI.h"
#include "UI/Title.h"
#include "actor/Bonfire.h"
#include "actor/BonfirePlayer.h"
#include "game/scene/ActorQuery.h"
#include "game/scene/SceneManager.h"

void TitleScene::LoadActors() {
    // タイトル
    mTitleID = mActorQuery->CreateUI<Title, BonfireUIDeps,
                                     TypeLists<RenderDB, StateManager>>();

    // Bonfire
    auto bonfireID =
        mActorQuery->CreateActor<Bonfire, BonfireDeps, TypeLists<RenderDB>>();

    // player
    auto playerID =
        mActorQuery
            ->CreateActor<BonfirePlayer, BonfirePlayerDeps,
                          TypeLists<ActorsSystem, RenderDB, AudioSystem>>();

    auto player = mActorQuery->GetActor<BonfirePlayer>(playerID);
    auto bonfire = mActorQuery->GetActor<Bonfire>(bonfireID);
    if (bonfire && player) {
        player->SetFieldRange(mFieldMin, mFieldMax);
        player->SetBonfireID(bonfireID);
        bonfire->SetPlayer(playerID);
    }

    // bonfire と player を別のSceneで使うため保存
    SceneContext playerIDContext{};
    playerIDContext.actorID = playerID;
    mSceneManagerData->emplace(mPlayerIDTag, playerIDContext);

    SceneContext bonfireIDContext{};
    bonfireIDContext.actorID = bonfireID;
    mSceneManagerData->emplace(mBonfireIDTag, bonfireIDContext);
}

void TitleScene::UnloadActors() {}

void TitleScene::TickRules() {}

std::string TitleScene::PollNextScene() {
    auto title = mActorQuery->GetActor<Title>(mTitleID);
    if (title && title->GetState() == UIScreen::EClosing) {
        return SceneName::game.data();
    } else if (!title) {
        return SceneName::game.data();
    }
}
