#pragma once

#include <vector>

#include "SDL.h"
#include "base/GameBase.h"

template <typename InputState>
class ObjectsSystemBase;
template <typename InputState>
class InputSystemBase;

// ゲームプログラムにおける処理の順序などを保証するクラス
// Game
template <typename InputState>
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

    float CalculateDeltatime() override;

    class ObjectsSystemBase<InputState>* mActorsSystem;
    class InputSystemBase<InputState>* mInputSystem;
    class Renderer* mRenderer;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

   public:
    Game();

    bool Initialize() override;
    void Shutdown() override;
};
