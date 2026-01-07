#include "BonfireGame.h"

#include "core/Math.h"
#include "game/Game.h"
#include "game/audio/AudioSystem.h"
#include "game/object/ActorsSystem.h"
#include "input/InputSystem.h"
#include "renderer/Renderer.h"

BonfireGame::BonfireGame() {
    mFieldMin = Vector2(-1500, -500);
    mFieldMax = Vector2(500, 1500);
}
