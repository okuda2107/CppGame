#pragma once
#include "Actor.h"

class Bonfire : public Actor {
    float mTime;
    float mLimit;
    // ロードした瞬間から動いてしまう．
    // Title画面では更新処理はしてほしくないので，更新処理をするかしないかのフラグ
    bool mIsRunning;
    bool mFinished;

    // 薪をくべられたか
    bool mAddWood;

    // 簡単のため，BonfirePlayerの位置をこちらで把握
    class BonfirePlayer* mPlayer;

    class SoundHandler* mEvent;

    const float cMaxLimit;

   public:
    Bonfire(class Game* game);

    void UpdateActor(float deltatime) override;

    void SetRunning() { mIsRunning = true; }
    void AddWood() { mAddWood = true; }
    void SetPlayer(class BonfirePlayer* player) { mPlayer = player; }

    float GetTime() { return mTime; }
    bool GetFinished() { return mFinished; }
};
