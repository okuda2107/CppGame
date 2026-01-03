#pragma once
#include "runtime/RuntimeData.h"

class GameCore {
   public:
    class RenderDB* mRenderDB;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

    class StateManager* mStateManager;

    class SceneManager* mSceneManager;

    GameFrameResult mFrameResult;

    GameCore();
    ~GameCore();

    bool Initialize();

    void ProcessInput(const class InputState& state);

    const struct RenderData& GenerateRenderData();
};
