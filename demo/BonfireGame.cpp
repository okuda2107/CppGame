#include "BonfireGame.h"

#include "core/Math.h"
#include "game/Game.h"
#include "game/audio/AudioSystem.h"
#include "game/object/ActorsSystem.h"
#include "input/InputSystem.h"
#include "renderer/Renderer.h"

BonfireGame::BonfireGame(GameCore* core, ActorsSystem* system)
    : Game<InputState>(core, system) {
    mFieldMin = Vector2(-1500, -500);
    mFieldMax = Vector2(500, 1500);
}

void BonfireGame::InputHandle(const InputState& state) {
    auto iter = state.EventMap.find(SDL_QUIT);
    if (iter != state.EventMap.end()) {
        mCore->mState.mState = RuntimeState::EQuit;
    }
}
