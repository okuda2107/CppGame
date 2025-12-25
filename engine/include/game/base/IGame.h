#pragma once

class IGame {
   public:
    IGame() = default;
    virtual ~IGame() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    virtual void IProcessInput(const struct InputStateBase& state) = 0;
    virtual const struct GameDataBase& IUpdate(
        float deltatime, const struct GameMetricsBase& metrics) = 0;
    virtual const struct RenderDataBase& IGenerateRenderData() = 0;
};
