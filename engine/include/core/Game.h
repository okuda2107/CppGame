#pragma once

#include <vector>

#include "GameBase.h"
#include "SDL.h"

// ゲームプログラムにおける処理の順序などを保証するクラス
class Game : public GameBase {
   public:
    enum GameState {
        EGameplay,
        EPaused,
        EQuit,
    };

   protected:
    Uint32 mTicksCount;

    bool mUpdatingActors;

    GameState mState;

    bool IsGameLoop() override { return mState != EQuit; }

    void ProcessInput() override;
    float CalculateDeltatime() override;
    void UpdateGame(float deltatime) override;
    void GenerateOutput() override;

    class ObjectsSystemBase* mActorsSystem;

   public:
    Game();

    bool Initialize() override;
    void Shutdown() override;
};
