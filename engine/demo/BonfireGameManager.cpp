#include "BonfireGameManager.h"

#include "Bonfire.h"
#include "BonfirePlayer.h"
#include "Game.h"
#include "GameOverUI.h"
#include "InputSystem.h"
#include "Title.h"

BonfireGameManager::BonfireGameManager(class Game* game)
    : Actor(game), mState(ETitle), mBonfire(nullptr), mPlayer(nullptr) {
    InitLoad();
}

BonfireGameManager::~BonfireGameManager() {
    if (mBonfire && mBonfire->GetState() != Actor::State::EDead)
        mBonfire->SetState(Actor::State::EDead);
    if (mPlayer && mPlayer->GetState() != Actor::State::EDead)
        mPlayer->SetState(Actor::State::EDead);
}

void BonfireGameManager::UpdateActor(float deltatime) {
    switch (mState) {
        case ETitle: {
            // InitLoadで必ず ETitleが設定される かつ Title画面が生成されるので，ETitleのまま，mIsTtileFinishedがtrueにならないことはない．
            // titleがトリガー
            if (mIsTitleFinished) {
                mPlayer->SetAnimLookDown();
                mPlayer->Initialize();
                mBonfire->SetRunning();
                mState = EPlaying;
            }
            break;
        }
        case EPlaying: {
            // Bonfireがトリガー
            if (mBonfire && mBonfire->GetFinished()) {
                mBonfire->SetState(Actor::State::EDead);
                mTime = mBonfire->GetTime();
                mBonfire = nullptr;
                mPlayer->SetAnimLookUp();
                mState = EAnim;
            }
            break;
        }
        case EAnim: {
            // 空見上げモーション中
            if (mPlayer && !mPlayer->GetAnimLookUp()) {
                auto gameOverUI = new GameOverUI(GetGame());
                gameOverUI->SetTime(mTime);
                gameOverUI->SetParent(this);
                mState = EResult;
            }
        }
        case EResult: {
            // GameOverUIがトリガー
            if (mIsResultFinished) {
                InitLoad();
            }
            break;
        }
        default:
            // 例外処理
            InitLoad();
            break;
    }
}

void BonfireGameManager::InitLoad() {
    mState = ETitle;
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

    mBonfire->SetPlayer(mPlayer);

    // 変数の初期化
    mTime = 0.0f;
    mIsTitleFinished = false;
    mIsResultFinished = false;
}
