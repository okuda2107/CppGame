#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "AudioSystem.h"
#include "SDL.h"
#include "SDL_image.h"

class Game {
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void UpdateActors(float deltatime);

    void LoadData();
    void UnloadData();

    class Renderer* mRenderer;
    class AudioSystem* mAudioSystem;
    class InputSystem* mInputSystem;
    class PhysWorld* mPhysWorld;

    bool mIsRunning;
    Uint32 mTicksCount;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    bool mUpdatingActors;

   public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    class Renderer* GetRenderer() { return mRenderer; }
    class AudioSystem* GetAudioSystem() { return mAudioSystem; }
    class InputSystem* GetInputSystem() { return mInputSystem; }
    class PhysWorld* GetPhysWorld() { return mPhysWorld; }
};
