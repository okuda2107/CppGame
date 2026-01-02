#pragma once
#include "runtime/RuntimeData.h"

class GameCore {
   public:
    class RenderDB* mRenderDB;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

    class SceneManager* mSceneManager;

    GameState mState;

    GameCore();
    ~GameCore();

    bool Initialize();

    // Actorのupdateの前に動かす
    void BeforeUpdate(float deltatime);

    // Actorのupdateの後に動かす
    void AfterUpdate(float deltatime);

    // 各種objectの削除処理
    void DeleteObject();

    const struct RenderData& GenerateRenderData();
};
