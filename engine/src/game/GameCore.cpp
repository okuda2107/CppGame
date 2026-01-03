#include "game/GameCore.h"

#include "SDL.h"
#include "game/RuntimeRequestManager.h"
#include "game/StateManager.h"
#include "game/UI/UIScreen.h"
#include "game/UI/UISystem.h"
#include "game/audio/AudioSystem.h"
#include "game/scene/SceneManager.h"
#include "input/InputState.h"
#include "renderer/RenderDB.h"
#include "renderer/RenderData.h"

GameCore::GameCore() {
    mRenderDB = new RenderDB();
    mAudioSystem = new AudioSystem();
    mUISystem = new UISystem();
    mStateManager = new StateManager();
    mReqManager = new RuntimeRequestManager();
    mReqManager->mInputSystemMetricsRequest.mRelativeMouseMode = true;
}

GameCore::~GameCore() {
    delete mUISystem;
    delete mAudioSystem;
    delete mRenderDB;
    delete mStateManager;
    delete mReqManager;
}

bool GameCore::Initialize() {
    try {  // 初期化に失敗したら初期状態にロールバックを行う
        if (!mRenderDB->Initialize()) {
            throw std::runtime_error("Failed to Initialize RenderDB");
        }

        if (!mAudioSystem->Initialize()) {
            throw std::runtime_error("Failed to initialize audio system");
        }
    } catch (const std::runtime_error& e) {
        SDL_Log(e.what());
        delete mRenderDB;
        delete mAudioSystem;
        mRenderDB = new RenderDB();
        mAudioSystem = new AudioSystem();

        return false;
    }

    return true;
}

void GameCore::ProcessInput(const InputState& state) {
    auto iter = state.EventMap.find(SDL_QUIT);
    if (iter != state.EventMap.end()) {
        mFrameResult.mIsGameLoop = false;
    }

    if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == EReleased) {
        mFrameResult.mIsGameLoop = false;
    }
}

const RenderData& GameCore::GenerateRenderData() {
    if (!mUISystem->GetUIStack().empty())
        mRenderDB->SetUI(&mUISystem->GetUIStack());
    else
        mRenderDB->SetUI(nullptr);
    return mRenderDB->GetData();
}
