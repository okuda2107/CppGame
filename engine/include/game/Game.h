#pragma once
#include <type_traits>

#include "base/GameBase.h"
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
    class ActorFactory* mActorFactory;

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
        scene->SetActorFactory(mActorFactory);
        scene->SetDataRef(mSceneManager->mData);
        return mSceneManager->SetScene(tag, scene);
    }
};
