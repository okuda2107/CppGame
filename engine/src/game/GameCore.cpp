#include "game/GameCore.h"

#include "SDL.h"
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
