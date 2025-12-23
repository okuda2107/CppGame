#include "game/GameCore.h"

#include "SDL.h"
#include "game/UI/UIScreen.h"
#include "game/UI/UISystem.h"
#include "game/audio/AudioSystem.h"
#include "renderer/RenderDB.h"
#include "renderer/RenderData.h"

bool GameCore::Initialize() {
    mRenderDB = new RenderDB();
    if (!mRenderDB->Initialize()) {
        SDL_Log("Failed to initialize render database");
        delete mRenderDB;
        mRenderDB = nullptr;
        return false;
    }

    mAudioSystem = new AudioSystem();
    if (!mAudioSystem->Initialize()) {
        SDL_Log("Failed to initialize audio system");
        delete mAudioSystem;
        mAudioSystem = nullptr;
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
