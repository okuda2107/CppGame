#include "core/base/GameBase.h"

void GameBase::RunLoop() {
    while (IsGameLoop()) {
        ProcessInput();
        UpdateGame(CalculateDeltatime());
        GenerateOutput();
    }
}
