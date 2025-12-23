#include "RuntimeData.h"
#include "SDL.h"
#include "base/RuntimeSystemBase.h"

using Metrics = MetricsBundle<GameMetricsBase, InputSystemMetrics>;

class RuntimeSystem : public RuntimeSystemBase<GameState, Metrics> {
    Uint32 mTicksCount;
    RuntimeState mState;

   public:
    bool Initialize();
    void Shutdown();

    bool IsRunning();

    void BeginFrame();
    void EndFrame();

    void ProcessGameData(const RuntimeState& state);
};
