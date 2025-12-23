#pragma once
#include "base/GameBase.h"
#include "runtime/RuntimeSystem.h"

template <typename InputState>
class ObjectsSystemBase;

template <typename InputState>
class Game : public GameBase<InputState, struct RenderData, struct GameState,
                             struct GameMetrics> {
   protected:
    class ObjectsSystemBase<InputState>* mActorsSystem;
    class RenderDB* mRenderDB;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

    GameState mState;

   public:
    bool Initialize() override;
    void Shutdown() override;

    void ProcessInput(const InputState& state) override;
    const struct GameState& Update(float deltatime,
                                   const struct GameMetrics& metrics) override;
    const struct RenderData& GenerateRenderData() override;

    class ObjectSystemBase<InputState>* GetObjectSystem() {
        return mActorsSystem;
    }
    class RenderDB* GetRenderDB() { return mRenderDB; }
    class AudioSystem* GetAudioSystem() { return mAudioSystem; }
    class UISystem* GetUISystem() { return mUISystem; }
};

#include "Game.inl"
