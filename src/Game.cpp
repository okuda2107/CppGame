#include "Game.h"
#include "Actor.h"
#include "Renderer.h"
// #include "AudioSystem.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "InputComponent.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "LevelLoader.h"
#include "glew.h"
#include <vector>
#include <algorithm>

Game::Game() : mIsRunning(true), mTicksCount(0), mUpdatingActors(false), mRenderer(nullptr) {}

bool Game::Initialize() {
	if (int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Failed to Initialize SDL:%s", SDL_GetError());
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1024.0f, 768.0f)) {
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	// mAudioSystem = new AudioSystem(this);
	// if (!mAudioSystem->Initialize()) {
	// 	SDL_Log("Failed to initialize audio system");
	// 	delete mAudioSystem;
	// 	mAudioSystem = nullptr;
	// 	return false;
	// }

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event mEvent;
	while (SDL_PollEvent(&mEvent)) {
		switch (mEvent.type)
			case SDL_QUIT:
				mIsRunning = false;
				break;
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->ProcessInput(state);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltatime > 0.05f) {
		deltatime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// mAudioSystem->Update(deltatime);

	UpdateActors(deltatime);
}

void Game::GenerateOutput() {
	mRenderer->Draw();
}

void Game::Shutdown() {
	UnloadData();
	if (mRenderer) {
		mRenderer->Shutdown();
	}
	// if (mAudioSystem) {
	// 	mAudioSystem->Shutdown();
	// }

	SDL_Quit();
}

void Game::AddActor(class Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.push_back(actor);
	} else {
		mActors.push_back(actor);
	}
}

void Game::RemoveActor(class Actor* actor) {
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end()) {
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) {
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::UpdateActors(float deltatime) {
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltatime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors) {
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<class Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetState() == Actor::State::EDead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors) {
		delete actor;
	}
}

void Game::LoadData() {
	LevelLoader::LoadLevel(this, "Assets/Level.json");
	// Create actors
	Actor* a = new Actor(this);
	a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
	a->SetScale(100.0f);
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	a->SetRotation(q);
	MeshComponent* mc = new MeshComponent(a);
	mc->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));
	InputComponent* ic = new InputComponent(a);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::Pi / 2);
	ic->SetXKey(SDL_SCANCODE_C);
	ic->Setantikey(SDL_SCANCODE_Z);
}

void Game::UnloadData() {
	while (!mActors.empty()) {
		delete mActors.back();
	}

	if (mRenderer) {
		mRenderer->UnloadData();
	}
	//erase()はメモリの解放はしないが、メモリの内容をnullにする
}
