#pragma once
#include "game/audio/SoundHandler.h"
#include "game/object/Actor.h"

struct BonfireDeps : ActorDeps {
    class RenderDB& renderDB;

    BonfireDeps(class RenderDB& db) : ActorDeps(), renderDB(db) {}
};

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
    ActorID mPlayerID;

    SoundHandler mEvent;

    const float cMaxLimit;

    class ActorsSystem& mActorsSystem;

   public:
    Bonfire(class ActorsSystem* system, BonfireDeps& deps);

    void UpdateActor(float deltatime) override;

    void SetRunning() { mIsRunning = true; }
    void AddWood() { mAddWood = true; }
    void SetPlayer(ActorID id) { mPlayerID = id; }

    float GetTime() { return mTime; }
    bool GetFinished() { return mFinished; }
};
