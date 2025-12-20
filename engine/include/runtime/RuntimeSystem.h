#include "SDL.h"
#include "base/RuntimeSystemBase.h"

struct GameMetrics {};
struct RendererMetrics {};

using Metrics = MetricsBundle<GameMetrics, RendererMetrics>;

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
