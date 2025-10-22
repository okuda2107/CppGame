#pragma once

#include "Actor.h"

// demoゲームの "たき火ゲーム" において全体の流れを管理するアクター
class BonfireGameManager : public Actor {
    enum State {
        EPlaying,
        EAnim,
    };

    // ゲームの状態
    BonfireGameManager::State mState;

    // 共有変数
    float mTime;

    // シーン遷移で状態管理をするもの
    class Bonfire* mBonfire;
    class BonfirePlayer* mPlayer;
    // 枝を生成するActorも必要？

    // ステージの初期化
    void InitLoad();

    friend class GameOverUI;

   public:
    BonfireGameManager(class Game* game);
    ~BonfireGameManager();

    void UpdateActor(float deltatime) override;

    class BonfirePlayer* GetPlayer() { return mPlayer; }
};
