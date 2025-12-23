#include "SDL.h"
#include "base/MetricsBase.h"
#include "base/RuntimeSystemBase.h"

enum class RuntimeState;

struct GameState : GameDataBase {
    RuntimeState mState;
};

struct InputSystemMetrics : InputSystemMetricsBase {
    // 相対マウスモードを有効 / 無効
    bool mRelativeMouseMode;
};

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
