#pragma once

#include "SDL.h"

// Gameのグローバルな設定や状態変数を持つ
class Game {
   public:
    enum GameState {
        EGameplay,
        EPaused,
        EQuit,
    };

   private:
    Uint32 mTicksCount;
    float mDeltatime;

    GameState mState;

   public:
    Game();

    bool Initialize();
    void Shutdown();

    bool IsGameLoop();

    float GetDeltatime() { return mDeltatime; }

    GameState GetState() { return mState; }
    void SetState(GameState state) { mState = state; }
};
