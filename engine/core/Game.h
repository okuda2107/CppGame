#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "AudioSystem.h"
#include "SDL.h"
#include "SDL_image.h"
#include "api/OpenAL/Bank.h"
#include "api/OpenAL/Event.h"

typedef AudioSystem<OpenAL::Bank, OpenAL::Event> Audio;

class Game {
   public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    class Renderer* GetRenderer() { return mRenderer; }
    Audio* GetAudioSystem() { return mAudioSystem; }

   private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void UpdateActors(float deltatime);

    void LoadData();
    void UnloadData();

    class Renderer* mRenderer;
    Audio* mAudioSystem;

    bool mIsRunning;
    Uint32 mTicksCount;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    bool mUpdatingActors;
};
