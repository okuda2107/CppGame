#include "BonfireGame.h"

#include "audio/OpenAL/System.h"
#include "core/ActorsSystem.h"
#include "core/Game.h"
#include "input/KeyboardAndMouse/InputSystem.h"
#include "renderer/OpenGL/Renderer.h"

BonfireGame::BonfireGame() {
    mGame = new Game();
    mActorsSystem = new ActorsSystem();
    mInputSystem = new KeyboardAndMouse::InputSystem();
    mRenderer = new OpenGL::Renderer();
    mAudioSystem = new OpenAL::System();
    mFieldMin = new Vector2(-1500, -500);
    mFieldMax = new Vector2(500, 1500);
}

bool BonfireGame::Initialize() {
    if (!mGame->Initialize()) return false;

    if (!mInputSystem->Initialize()) {
        SDL_Log("Failed to initialize input system");
        delete mInputSystem;
        mInputSystem = nullptr;
        return false;
    }

    if (!mRenderer->Initialize(1024.0f, 768.0f)) {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }

    if (!mAudioSystem->Initialize()) {
        SDL_Log("Failed to initialize audio system");
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }

    LoadData();

    return true;
}

void BonfireGame::RunLoop() {
    while (mGame->IsGameLoop()) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void BonfireGame::ProcessInput() {
    // 入力状態の保存
    mInputSystem->PrepareForUpdate();

    // ユーザからの入力イベント or 入力機器の状態をポーリング (定期問い合わせ)
    // イベントが入力されてたら，イベントを処理．
    KeyboardAndMouse::Event event;
    while (KeyboardAndMouse::PollEvent(&event)) {
        switch (event.type) {
            case KeyboardAndMouse::QUIT:
                mGame->SetState(Game::EQuit);
                break;
            case KeyboardAndMouse::MOUSEWHEEL:
                mInputSystem->ProcessEvent(event);
                break;
            default:
                break;
        }
    }

    // ポーリングで入力状態更新
    mInputSystem->Update();

    // 入力に対してGameを反応させる
    if (mInputSystem->GetState().Keyboard->GetKeyState(SDL_SCANCODE_ESCAPE) ==
        EReleased) {
        mGame->SetState(Game::EQuit);
    }
}

void BonfireGame::UpdateGame() {
    mAudioSystem->Update(mGame->GetDeltatime());

    mActorsSystem->UpdateActors(mGame->GetDeltatime());

    //UIの処理
}

void BonfireGame::GenerateOutput() { mRenderer->Draw(); }

void BonfireGame::Shutdown() {
    if (mActorsSystem) mActorsSystem->UnloadActors();
    if (mInputSystem) mInputSystem->Shutdown();
    if (mRenderer) mRenderer->Shutdown();
    if (mAudioSystem) mAudioSystem->Shutdown();

    if (mGame) mGame->Shutdown();
}

void BonfireGame::LoadData() {
    mAudioSystem->LoadBank("Assets/Master.bank");
    // LevelLoader::LoadLevel(this, "Assets/Level.gplevel");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            auto f = new Floor(mActorsSystem);
            f->SetPosition(Vector3(-1000 * i, 1000 * j, -70));
        }
    }
    new BackDome(mActorsSystem);

    new BonfireGameManager(mActorsSystem);

    // 環境光
    mRenderer->SetAmbientLight(Vector3(0.1, 0.1, 0.2));
}
