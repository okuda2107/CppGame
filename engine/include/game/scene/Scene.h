#pragma once

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
};

class Scene {
   protected:
    class ActorsSystem& mActorsSystem;
    class RenderDB& mRenderDB;
    class AudioSystem& mAudioSystem;
    // class PhysicsSystem& mPhysicsSystem;
    class UISystem& mUISystem;

   public:
    Scene(struct SceneCreateDeps& scd)
        : mRenderDB(scd.renderDB),
          mAudioSystem(scd.audioSystem),
          mUISystem(scd.uiSystem) {}
};
