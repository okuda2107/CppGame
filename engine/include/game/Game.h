#pragma once
#include <type_traits>

#include "base/GameBase.h"
#include "game/UI/UIScreen.h"
#include "game/object/Actor.h"
#include "game/scene/ActorQuery.h"
#include "input/InputState.h"
#include "renderer/RenderData.h"
#include "runtime/RuntimeData.h"
#include "scene/Scene.h"
#include "scene/SceneManager.h"

class Game : public GameBase<InputState, RenderData, GameFrameResult,
                             GameMetricsBase> {
    class ActorsSystem* mActorsSystem;
    class RenderDB* mRenderDB;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

    class StateManager* mStateManager;

    class SceneManager* mSceneManager;
    class ActorQuery* mActorQuery;

    GameFrameResult mFrameResult;
    class RuntimeRequestManager* mReqManager;

   public:
    Game();
    virtual ~Game();

    bool Initialize();

    void ProcessInput(const InputState& state) override;
    const struct GameFrameResult& Update(
        float deltatime, const struct GameMetricsBase& metrics) override;
    const struct RenderData& GenerateRenderData() override;

    template <typename TScene>
    bool LoadScene(const std::string& tag) {
        static_assert(std::is_base_of<Scene, TScene>::value,
                      "TScene must derive from Scene");
        TScene* scene = new TScene();
        scene->SetActorQuery(mActorQuery);
        scene->SetDataRef(&mSceneManager->mData);
        return mSceneManager->SetScene(tag, scene);
    }

    bool SetEntryScene(const std::string& tag) {
        return mSceneManager->SetEntryScene(tag);
    }

    // grobal objectなどのロード
    template <typename TActor, typename TDeps, typename TLists>
    ActorID CreateActor() {
        return mActorQuery->CreateActor<TActor, TDeps, TLists>();
    }

    template <typename TUI, typename TDeps, typename TLists>
    UIID CreateUI() {
        return mActorQuery->CreateUI<TUI, TDeps, TLists>();
    }
};
