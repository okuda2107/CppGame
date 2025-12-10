#pragma once
#include <vector>

#include "SDL.h"

struct GameConfig {
    class InputSysytemBase* inputSystem;
    class AudioSystemBase* audioSystem;
    class RendererBase* renderer;
    class PhysicsSystemBase* physSystem;
};

class Game {
    class InputSysytemBase* mInputSystem;
    class AudioSystemBase* mAudioSystem;
    class RendererBase* mRenderer;
    class PhysicsSystemBase* mPhysSystem;

    Uint32 mTicksCount;
    float mDeltatime;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

   public:
    bool Initialize();
    void Shutdown();

    bool isGameLoop();

    void ProcessInput(class InputState& inputState);
    void Update();
    void GenerateOutput();

    float GetDeltatime() { return mDeltatime; }
};
