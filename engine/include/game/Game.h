#pragma once
#include "GameCore.h"
#include "base/GameBase.h"
#include "game/UI/UIScreen.h"
#include "game/UI/UISystem.h"
#include "object/base/ObjectsSystemBase.h"

template <typename InputState>
class Game : public GameBase<InputState, struct RenderData, struct GameState,
                             struct GameMetrics> {
   protected:
    class GameCore* mCore;

    ObjectsSystemBase<InputState>* mActorsSystem;

    // ユーザ定義の入力処理
    virtual void InputHandle(const InputState& state) {};

   public:
    Game(class GameCore* core, ObjectsSystemBase<InputState>* system)
        : mCore(core), mActorsSystem(system) {}

    bool Initialize() override {
        mActorsSystem = new ObjectsSystemBase<InputState>();
        return mCore->Initialize();
    }
    void Shutdown() override {
        mActorsSystem->UnloadObjects();
        mCore->Shutdown();
    }

    void ProcessInput(const InputState& state) override {
        InputHandle(state);

        // 入力に対して，ゲームオブジェクト，UIを反応させる
        if (mCore->mState.mState == EGameplay) {
            mActorsSystem->ProcessInput(state);
        } else if (!mUIStack.empty()) {
            mCore->mUISystem->GetUIStack().back()->ProcessInput(state);
        }
    }
    const struct GameState& Update(float deltatime,
                                   const struct GameMetrics& metrics) override {
        mCore->BeforeUpdate(deltatime);
        mActorsSystem->UpdateObjects(deltatime);
        mCore->AfterUpdate(deltatime);
        return mCore->mState;
    }
    const struct RenderData& GenerateRenderData() override {
        return mCore->GenerateRenderData();
    }

    class ObjectSystemBase<InputState>* GetObjectSystem() {
        return mActorsSystem;
    }
    class RenderDB* GetRenderDB() { return mCore.mRenderDB; }
    class AudioSystem* GetAudioSystem() { return mCore.mAudioSystem; }
    // class PhysicsSystem* GetPhysicsSystem() { return mCore.mPhysicsSystem; }
    class UISystem* GetUISystem() { return mCore.mUISystem; }
};
