#include "game/GameCore.h"

#include "SDL.h"
#include "game/UI/UIScreen.h"
#include "game/UI/UISystem.h"
#include "game/audio/AudioSystem.h"
#include "game/scene/SceneManager.h"
#include "renderer/RenderDB.h"
#include "renderer/RenderData.h"

GameCore::GameCore() {
    mRenderDB = new RenderDB();
    mAudioSystem = new AudioSystem();
    mUISystem = new UISystem();
}

GameCore::~GameCore() {
    delete mUISystem;
    delete mAudioSystem;
    delete mRenderDB;
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

const RenderData& GameCore::GenerateRenderData() {
    if (!mUISystem->GetUIStack().empty())
        mRenderDB->SetUI(&mUISystem->GetUIStack());
    else
        mRenderDB->SetUI(nullptr);
    return mRenderDB->GetData();
}
