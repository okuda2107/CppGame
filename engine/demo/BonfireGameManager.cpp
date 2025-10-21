#include "BonfireGameManager.h"

#include "Bonfire.h"
#include "BonfirePlayer.h"
#include "Game.h"
#include "GameOverUI.h"
#include "InputSystem.h"
#include "Title.h"

BonfireGameManager::BonfireGameManager(class Game* game)
    : Actor(game), mState(ETitle) {
    InitLoad();
}

BonfireGameManager::~BonfireGameManager() {}

void BonfireGameManager::UpdateActor(float deltatime) {
    switch (mState) {
        case ETitle: {
            // titleがトリガー
            if (mTitle && mTitle->GetFinished()) {
                mTitle->Close();
                mTitle = nullptr;
                mPlayer->SetAnimLookDown();
                mState = EPlaying;
            }
            break;
        }
        case EPlaying: {
            // Bonfireがトリガー
            if (mBonfire && mBonfire->GetFinished()) {
                mBonfire->SetState(Actor::State::EDead);
                mTime = mBonfire->GetTime();
                mPlayer->SetAnimLookUp();
                mState = EAnim;
            }
            break;
        }
        case EAnim: {
            // 空見上げモーション中
            if (mPlayer && !mPlayer->GetAnimLookUp()) {
                mGameOverUI = new GameOverUI(GetGame());
                mGameOverUI->SetTime(mTime);
                mState = EResult;
            }
        }
        case EResult: {
            // GameOverUIがトリガー
            if (mGameOverUI && mGameOverUI->GetFinished()) {
                mGameOverUI->Close();
                mGameOverUI = nullptr;
                InitLoad();
                mState = ETitle;
            }
            break;
        }
        default:
            break;
    }
}

void BonfireGameManager::InitLoad() {
    GetGame()->SetState(Game::GameState::EPaused);
    if (mTitle && mTitle->GetState() != UIScreen::EClosing) mTitle->Close();
    mTitle = new Title(GetGame());
    if (mBonfire && mBonfire->GetState() != Actor::State::EDead)
        mBonfire->SetState(Actor::State::EDead);
    mBonfire = new Bonfire(GetGame());
    if (mPlayer && mPlayer->GetState() != Actor::State::EDead)
        mPlayer->SetState(Actor::State::EDead);
    mPlayer = new BonfirePlayer(GetGame());
    mPlayer->SetPitchAngular(Math::Pi / 4);
    mPlayer->SetForwardSpeed(60.0f);
    mPlayer->SetStrafeSpeed(60.0f);

    // 変数の初期化
    mTime = 0.0f;
}
