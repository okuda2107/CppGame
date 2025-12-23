#include "SDL.h"
#include "base/MetricsBase.h"
#include "base/RuntimeSystemBase.h"

struct InputSystemMetrics : InputSystemMetricsBase {
    // 相対マウスモードを有効 / 無効
    bool mRelativeMouseMode;
};

using Metrics = MetricsBundle<GameMetricsBase, InputSystemMetrics>;

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
