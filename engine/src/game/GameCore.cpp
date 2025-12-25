#include "game/GameCore.h"

#include "SDL.h"
#include "game/UI/UIScreen.h"
#include "game/UI/UISystem.h"
#include "game/audio/AudioSystem.h"
#include "renderer/RenderDB.h"
#include "renderer/RenderData.h"

GameCore::GameCore() {
    mRenderDB = new RenderDB();
    mAudioSystem = new AudioSystem();
    mUISystem = new UISystem();
}

GameCore::~GameCore() {
    Shutdown();
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

void GameCore::Shutdown() {
    if (mRenderDB) mRenderDB->Shutdown();
    if (mAudioSystem) {
        mAudioSystem->UnloadAllBanks();
        mAudioSystem->Shutdown();
    }
}

void GameCore::BeforeUpdate(float deltatime) {
    mAudioSystem->Update(deltatime);
}

void GameCore::AfterUpdate(float deltatime) {
    // UIの更新
    for (auto ui : mUISystem->GetUIStack()) {
        if (ui->GetState() == UIScreen::EActive) ui->Update(deltatime);
    }

    // close状態のUIを削除
    auto iter = mUISystem->GetUIStack().begin();
    while (iter != mUISystem->GetUIStack().end()) {
        if ((*iter)->GetState() == UIScreen::EClosing) {
            delete *iter;
            iter = mUISystem->GetUIStack().erase(iter);
        } else {
            ++iter;
        }
    }
}

const RenderData& GameCore::GenerateRenderData() {
    if (!mUISystem->GetUIStack().empty())
        mRenderDB->SetUI(&mUISystem->GetUIStack());
    else
        mRenderDB->SetUI(nullptr);
    return mRenderDB->GetData();
}
