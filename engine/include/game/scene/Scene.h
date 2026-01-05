#pragma once
#include <string>
#include <unordered_map>

#include "runtime/RuntimeData.h"

struct SceneDeps {
    std::unordered_map<std::string, struct SceneContext>& sceneManagerData;
};

class Scene {
    friend class SceneManager;

   protected:
    class ActorFactory* mActorFactory;

    class ActorsSystem& mActorsSystem;
    class RenderDB& mRenderDB;
    class AudioSystem& mAudioSystem;
    // class PhysicsSystem& mPhysicsSystem;
    class UISystem& mUISystem;
    class StateManager& mStateManager;
    class RuntimeRequestManager& mRuntimeReqManager;
    std::unordered_map<std::string, struct SceneContext>& mSceneManagerData;

    /*
        外部からSceneをロードされ，SceneManagerを通さないことを防ぐため，
        SceneManagerをfriendクラスにして，Load / Unload をprotectedにする．
    */
    virtual void LoadActors() = 0;
    virtual void UnloadActors() = 0;

   public:
    Scene(struct SceneCreateDeps& scd)
        : mActorsSystem(scd.actorsSystem),
          mRenderDB(scd.renderDB),
          mAudioSystem(scd.audioSystem),
          mUISystem(scd.uiSystem),
          mStateManager(scd.stateManager),
          mRuntimeReqManager(scd.runtimeReqManager),
          mSceneManagerData(scd.sceneManagerData) {}

    virtual ~Scene() = default;

    // Gameの状態を監視し，必要なら各Actorに要求を出す
    virtual const struct GameState& TickRules() = 0;

    // SceneManagerに登録されているSceneのtag文字列を返す
    // 遷移しないときは空文字列を返す
    // 存在しないtag文字列を返すと，Logを出して，処理が続行される
    virtual std::string PollNextScene() = 0;
};
