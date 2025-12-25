#pragma once

class IInputSystem {
   public:
    IInputSystem() = default;
    virtual ~IInputSystem() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    virtual void IUpdate() = 0;

    virtual const struct InputStateBase& IGetState() const = 0;

    virtual void IProcessMetrics(
        const struct InputSystemMetricsBase& metrics) = 0;
};
