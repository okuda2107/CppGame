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

    const struct RenderData& GenerateRenderData();
};
