#pragma once

#include "Actor.h"

// demoゲームの "たき火ゲーム" において全体の流れを管理するアクター
class BonfireGameManager : public Actor {
    enum State {
        ETitle,
        EPlaying,
        EAnim,
        EResult,
    };

    // ゲームの状態
    BonfireGameManager::State mState;

    // 共有変数
    float mTime;

    // シーン遷移で状態管理をするもの
    bool mIsTitleFinished;
    class Bonfire* mBonfire;
    class BonfirePlayer* mPlayer;
    // 枝を生成するActorも必要？
    bool mIsResultFinished;

    // ステージの初期化
    void InitLoad();

    friend class Title;
    friend class GameOverUI;

   public:
    BonfireGameManager(class Game* game);
    ~BonfireGameManager();

    void UpdateActor(float deltatime) override;

    void SetTitleFinished() { mIsTitleFinished = true; }
    void SetResultFinished() { mIsResultFinished = true; }

    class Bonfire* GetBonfire() { return mBonfire; }
    class BonfirePlayer* GetPlayer() { return mPlayer; }
};
