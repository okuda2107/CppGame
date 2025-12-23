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
};
