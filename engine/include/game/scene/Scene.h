#pragma once
#include <string>
#include <unordered_map>

struct SceneCreateDeps {
    /*
        Sceneの生成ではactorの存在が前提となっているため，
        ObjectsSystemBaseではなく，
        ActorsSystemの方を依存関係に含める
    */
    class ActorsSystem& actorsSystem;
    class RenderDB& renderDB;
    class AudioSystem& audioSystem;
    // class PhysicsSystem& physicsSystem;
    class UISystem& uiSystem;
    std::unordered_map<std::string, struct SceneContext>& sceneManagerData;
};

class Scene {
    friend class SceneManager;

   protected:
    class ActorsSystem& mActorsSystem;
    class RenderDB& mRenderDB;
    class AudioSystem& mAudioSystem;
    // class PhysicsSystem& mPhysicsSystem;
    class UISystem& mUISystem;
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
          mSceneManagerData(scd.sceneManagerData) {}

    virtual ~Scene() = default;

    // Gameの状態を監視し，必要なら各Actorに要求を出す
    virtual void TickRules() {}

    // SceneManagerに登録されているSceneのtag文字列を返す
    // 遷移しないときは空文字列を返す
    // 存在しないtag文字列を返すと，Logを出して，処理が続行される
    virtual std::string PollNextScene() = 0;
};
