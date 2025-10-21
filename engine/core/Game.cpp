#include "Game.h"

#include <algorithm>
#include <vector>

#include "Actor.h"
#include "AudioSystem.h"
#include "Font.h"
#include "InputSystem.h"
#include "LevelLoader.h"
#include "MeshComponent.h"
#include "PauseMenu.h"
#include "PhysWorld.h"
#include "Renderer.h"
#include "SDL_ttf.h"
#include "Shader.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "UIScreen.h"
#include "VertexArray.h"
#include "api/OpenAL/System.h"
#include "glew.h"

Game::Game()
    : mGameState(EGameplay),
      mTicksCount(0),
      mUpdatingActors(false),
      mRenderer(nullptr) {}

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

    mAudioSystem = new OpenAL::System(this);
    if (!mAudioSystem->Initialize()) {
        SDL_Log("Failed to initialize audio system");
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }

    mInputSystem = new InputSystem(this);
    if (!mInputSystem->Initialize()) {
        SDL_Log("Failed to initialize input system");
        delete mInputSystem;
        mInputSystem = nullptr;
        return false;
    }

    mPhysWorld = new PhysWorld(this);

    // Initialize SDL_ttf
    if (TTF_Init() != 0) {
        SDL_Log("Failed to initialize SDL_ttf");
        return false;
    }

    LoadData();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop() {
    while (mGameState != EQuit) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    // 入力状態の保存
    mInputSystem->PrepareForUpdate();

    // ユーザからの入力イベント or 入力機器の状態をポーリング (定期問い合わせ)
    // イベントが入力されてたら，イベントを処理．
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mGameState = EQuit;
                ;
                break;
            case SDL_MOUSEWHEEL:
                // イベントドリブンで入力状態更新
                mInputSystem->ProcessEvent(event);
                break;
            case SDL_KEYDOWN:
                if (!event.key.repeat) {
                    if (mGameState == EGameplay)
                        HandleKeyPress(event.key.keysym.sym);
                    else if (!mUIStack.empty())
                        mUIStack.back()->HandleKeyPress(event.key.keysym.sym);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (mGameState == EGameplay) {
                    HandleKeyPress(event.button.button);
                } else if (!mUIStack.empty()) {
                    mUIStack.back()->HandleKeyPress(event.button.button);
                }
                break;
            default:
                break;
        }
    }

    // ポーリングで入力状態更新
    mInputSystem->Update();
    const InputState& state = mInputSystem->GetState();

    // 入力に対して，Gameクラスを反応させる
    if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased) {
        mGameState = EQuit;
    }

    // 入力に対して，ゲームオブジェクト，UIを反応させる
    if (mGameState == EGameplay) {
        mUpdatingActors = true;
        for (auto actor : mActors) {
            actor->ProcessInput(state);
        }
        mUpdatingActors = false;
    } else if (!mUIStack.empty()) {
        mUIStack.back()->ProcessInput(state);
    }
}

void Game::HandleKeyPress(int key) {
    switch (key) {
        case 'p':
            // Create pause menu
            new PauseMenu(this);
            break;
        default:
            break;
    }
}

void Game::UpdateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltatime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltatime > 0.05f) {
        deltatime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    mAudioSystem->Update(deltatime);

    UpdateActors(deltatime);

    // UIの更新
    for (auto ui : mUIStack) {
        if (ui->GetState() == UIScreen::EActive) {
            ui->Update(deltatime);
        }
    }
    // close状態のUIを削除
    auto iter = mUIStack.begin();
    while (iter != mUIStack.end()) {
        if ((*iter)->GetState() == UIScreen::EClosing) {
            delete *iter;
            iter = mUIStack.erase(iter);
        } else {
            ++iter;
        }
    }
}

void Game::GenerateOutput() { mRenderer->Draw(); }

void Game::Shutdown() {
    UnloadData();
    if (mRenderer) mRenderer->Shutdown();
    if (mAudioSystem) mAudioSystem->Shutdown();
    if (mInputSystem) mInputSystem->Shutdown();
    TTF_Quit();

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

Font* Game::GetFont(const std::string& fileName) {
    auto iter = mFonts.find(fileName);
    if (iter != mFonts.end()) {
        return iter->second;
    } else {
        Font* font = new Font(this);
        if (font->Load(fileName)) {
            mFonts.emplace(fileName, font);
        } else {
            font->Unload();
            delete font;
            font = nullptr;
        }
        return font;
    }
}

#include "BackDome.h"
#include "Bonfire.h"
#include "FPSActor.h"
#include "Floor.h"
#include "HUD.h"
void Game::LoadData() {
    mAudioSystem->LoadBank("Assets/Master.bank");
    // LevelLoader::LoadLevel(this, "Assets/Level.gplevel");
    new Bonfire(this);
    new Floor(this);
    new BackDome(this);
    FPSActor* fa = new FPSActor(this);
    fa->SetForwardSpeed(60.0f);
    fa->SetStrafeSpeed(60.0f);

    // UI
    // new HUD(this);

    // 環境光
    GetRenderer()->SetAmbientLight(Vector3(0.1, 0.1, 0.2));
}

void Game::UnloadData() {
    while (!mActors.empty()) {
        delete mActors.back();
    }

    if (mRenderer) {
        mRenderer->UnloadData();
    }
    // erase()は中身のメモリの解放はしない
    if (mAudioSystem) {
        mAudioSystem->UnloadAllBanks();
    }
}
