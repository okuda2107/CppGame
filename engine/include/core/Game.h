#pragma once

#include <vector>

#include "SDL.h"
#include "base/GameBase.h"

// ゲームプログラムにおける処理の順序などを保証するクラス
// Game
class Game : public GameBase {
   public:
    enum GameState {
        EGameplay,
        EPaused,
        EQuit,
    };

   protected:
    Uint32 mTicksCount;

    GameState mState;

    bool IsGameLoop() override { return mState != EQuit; }

    void ProcessInput() override;
    float CalculateDeltatime() override;
    void UpdateGame(float deltatime) override;

    class ActorsSystem* mActorsSystem;
    class InputSystem* mInputSystem;
    class Renderer* mRenderer;

   public:
    Game();

    virtual bool Initialize() override;
    virtual void Shutdown() override;
};
