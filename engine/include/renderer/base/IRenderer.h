#pragma once

class IRenderer {
   public:
    IRenderer() = default;
    virtual ~IRenderer() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    virtual void IDraw(const struct RenderDataBase& data) = 0;
};
