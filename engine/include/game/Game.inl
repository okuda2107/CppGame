#include "audio/AudioSystem.h"
#include "renderer/RenderDB.h"
#include "renderer/RenderData.h"
#include "runtime/RuntimeSystem.h"

template <typename InputState>
bool Game<InputState>::Initialize() {
    if (!mAudioSystem->Initialize()) {
        SDL_Log("Failed to initialize audio system");
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }

    return true;
}

template <typename InputState>
void Game<InputState>::Shutdown() {
    mActorsSystem->UnloadObjects();
}

template <typename InputState>
void Game<InputState>::ProcessInput(const InputState& state) {
    mActorsSystem->ProcessInput(state);
}

template <typename InputState>
const GameState& Game<InputState>::Update(float deltatime,
                                          const GameMetrics& _) {
    mActorsSystem->UpdateObjects(deltatime);
    return mState;
}

template <typename InputState>
const RenderData& GenerateRenderData() {
    return mRenderDB->GetData();
}
