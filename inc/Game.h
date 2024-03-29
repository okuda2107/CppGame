#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <unordered_map>
#include <string>

#include <iostream>

class Game {
    public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

	class Renderer* GetRenderer() { return mRenderer; }
	// class AudioSystem* GetAudioSystem() { return mAudioSystem; }

    private:
    void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void UpdateActors(float deltatime);

	void LoadData();
	void UnloadData();

	class Renderer* mRenderer;
	// class AudioSystem* mAudioSystem;

	bool mIsRunning;
	Uint32 mTicksCount;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	bool mUpdatingActors;
};
