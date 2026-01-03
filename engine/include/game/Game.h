#pragma once
#include "GameCore.h"
#include "base/GameBase.h"
#include "game/RuntimeRequestManager.h"
#include "game/StateManager.h"
#include "game/UI/UIScreen.h"
#include "game/UI/UISystem.h"
#include "game/audio/AudioSystem.h"
#include "game/object/base/ObjectsSystemBase.h"
#include "game/scene/SceneManager.h"
#include "renderer/RenderData.h"
#include "runtime/RuntimeData.h"

template <typename InputState>
class Game : public GameBase<InputState, RenderData, GameFrameResult,
                             GameMetricsBase> {
   protected:
    class GameCore* mCore;

    class ObjectsSystemBase<InputState>* mActorsSystem;

    // ユーザ定義の入力処理
    virtual void InputHandle(const InputState& state) {};

   public:
    Game(ObjectsSystemBase<InputState>* system) : mActorsSystem(system) {
        mCore = new GameCore();
    }
    virtual ~Game() { delete mCore; }

    bool Initialize() {
        if (!mCore->Initialize()) {
            return false;
        }
        return mCore->Initialize();
    }

    void ProcessInput(const InputState& state) override {
        InputHandle(state);

        // 終了方法は定義しておく
        mCore->ProcessInput(state);

        // 入力に対して，ゲームオブジェクト，UIを反応させる
        if (mCore->mStateManager->mState == GameState::EGameplay) {
            mActorsSystem->ProcessInput(state);
        } else if (!mCore->mUISystem->GetUIStack().empty()) {
            mCore->mUISystem->GetUIStack().back()->ProcessInput(state);
        }
    }
    const struct GameFrameResult& Update(
        float deltatime, const struct GameMetricsBase& metrics) override {
        mCore->mAudioSystem->Update(deltatime);
        mActorsSystem->UpdateObjects(deltatime);
        mCore->mUISystem->Update(deltatime);
        mCore->mSceneManager->Update();
        mCore->mFrameResult.mRelativeMouseMode =
            mCore->mReqManager->mInputSystemMetricsRequest.mRelativeMouseMode;
        return mCore->mFrameResult;
    }
    const struct RenderData& GenerateRenderData() override {
        return mCore->GenerateRenderData();
    }

    class ObjectsSystemBase<InputState>* GetObjectSystem() {
        return mActorsSystem;
    }
    class RenderDB* GetRenderDB() { return mCore->mRenderDB; }
    class AudioSystem* GetAudioSystem() { return mCore->mAudioSystem; }
    // class PhysicsSystem* GetPhysicsSystem() { return mCore->mPhysicsSystem; }
    class UISystem* GetUISystem() { return mCore->mUISystem; }

    class SceneManager* GetSceneManager() { return mCore->mSceneManager; }
};
