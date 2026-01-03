#pragma once

enum class GameState {
    EGameplay,
    EPause,
};

// Gameのループ状態を制御するためのクラス
class StateManager {
   public:
    StateManager() : mState(GameState::EGameplay) {}
    GameState mState;
};
