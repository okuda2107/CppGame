#pragma once
#include "base/MetricsBase.h"

enum class RuntimeState {
    EGameplay,
    EPaused,
    EQuit,
};

struct GameState : GameDataBase {
    RuntimeState mState;
};

struct InputSystemMetrics : InputSystemMetricsBase {
    // 相対マウスモードを有効 / 無効
    bool mRelativeMouseMode;
};
