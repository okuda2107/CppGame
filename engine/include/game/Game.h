#pragma once
#include "base/GameBase.h"

enum class RuntimeState;
struct GameMetrics;

template <typename InputState>
class ObjectsSystemBase;

template <typename InputState, typename RenderData>
class Game
    : public GameBase<InputState, RenderData, RuntimeState, GameMetrics> {
   protected:
    class ObjectsSystemBase<InputState>* mActorsSystem;
    class AudioSystem* mAudioSystem;
    // class PhysicsSystem* mPhysicsSystem;
    class UISystem* mUISystem;

   public:
    bool Initialize() override;
    void Shutdown() override;

    void ProcessInput(const InputState& state) override;
    const RuntimeState& Update(float deltatime,
                               const GameMetrics& metrics) override;
    const RenderData& GenerateRenderData() override;
};
