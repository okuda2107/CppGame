#include "RuntimeData.h"
#include "SDL.h"
#include "base/RuntimeSystemBase.h"

using Metrics = MetricsBundle<GameMetricsBase, InputSystemMetrics>;

class RuntimeSystem : public RuntimeSystemBase<GameState, Metrics> {
    Uint32 mTicksCount;
    RuntimeState mState;

    void Shutdown();

   public:
    RuntimeSystem();
    ~RuntimeSystem();

    bool Initialize();

    bool IsRunning() const override;

    void BeginFrame() override;
    void EndFrame() override;

    void ProcessGameData(const GameState& state);
};
