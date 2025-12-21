#include "SDL.h"
#include "base/MetricsBase.h"
#include "base/RuntimeSystemBase.h"

using Metrics = MetricsBundle<GameMetricsBase, RendererMetricsBase>;

enum class RuntimeState;

class RuntimeSystem : public RuntimeSystemBase<RuntimeState, Metrics> {
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
