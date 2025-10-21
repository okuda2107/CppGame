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

    // シーン遷移のトリガーとなるもの
    class Title* mTitle;
    class Bonfire* mBonfire;
    class BonfirePlayer* mPlayer;
    // 枝を生成するActorも必要？
    class GameOverUI* mGameOverUI;

    // ステージの初期化
    void InitLoad();

   public:
    BonfireGameManager(class Game* game);
    ~BonfireGameManager();

    void UpdateActor(float deltatime) override;
};
