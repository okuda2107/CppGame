#pragma once

template <typename RenderData>
class RendererBase {
   public:
    RendererBase() = default;
    virtual ~RendererBase() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    virtual void Draw(const RenderData& data) = 0;
};
