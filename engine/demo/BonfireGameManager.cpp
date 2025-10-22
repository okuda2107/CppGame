#include "BonfireGameManager.h"

#include "Bonfire.h"
#include "BonfirePlayer.h"
#include "Game.h"
#include "GameOverUI.h"
#include "InputSystem.h"
#include "Title.h"

BonfireGameManager::BonfireGameManager(class Game* game)
    : Actor(game), mState(EPlaying), mBonfire(nullptr), mPlayer(nullptr) {
    InitLoad();
}

BonfireGameManager::~BonfireGameManager() {}

void BonfireGameManager::UpdateActor(float deltatime) {
    // このステート処理ではなく，UIとの連携でシーン遷移
    // GameOverUIとの連携のため，mBonfireの状態をポーリング
    // finishedしたら発火
    if (mBonfire && mBonfire->GetFinished()) {
        mBonfire->SetState(Actor::State::EDead);
        mTime = mBonfire->GetTime();
        mPlayer->SetAnimLookUp();
        mState = EAnim;
    }
    // 空見上げモーションが終わるまでポーリング
    if (mState == EAnim && mPlayer && !mPlayer->GetAnimLookUp()) {
        auto gameOverUI = new GameOverUI(GetGame());
        gameOverUI->SetTime(mTime);
        gameOverUI->SetParent(this);
    }
}

void BonfireGameManager::InitLoad() {
    mState = EPlaying;
    auto title = new Title(GetGame());
    title->SetParent(this);
    if (mBonfire && mBonfire->GetState() != Actor::State::EDead)
        mBonfire->SetState(Actor::State::EDead);
    mBonfire = new Bonfire(GetGame());
    if (mPlayer && mPlayer->GetState() != Actor::State::EDead)
        mPlayer->SetState(Actor::State::EDead);
    mPlayer = new BonfirePlayer(GetGame());
    mPlayer->SetPitchAngular(-Math::Pi / 4);
    mPlayer->SetForwardSpeed(60.0f);
    mPlayer->SetStrafeSpeed(60.0f);

    // 変数の初期化
    mTime = 0.0f;
}
