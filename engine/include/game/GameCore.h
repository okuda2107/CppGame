#pragma once
#include "runtime/RuntimeSystem.h"

class GameCore {
   public:
    class RenderDB* mRenderDB;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

    GameState mState;

    bool Initialize();
    void Shutdown();

    // Actorのupdateの前に動かす
    void BeforeUpdate(float deltatime);

    // Actorのupdateの後に動かす
    void AfterUpdate(float deltatime);

    const struct RenderData& GenerateRenderData();
};
