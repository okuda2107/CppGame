#pragma once
#include "core/Math.h"
#include "game/Game.h"
#include "input/InputState.h"

class BonfireGame : public Game {
    Vector2 mFieldMin;
    Vector2 mFieldMax;

   public:
    BonfireGame();
};
