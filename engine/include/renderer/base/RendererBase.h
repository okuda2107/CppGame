#pragma once
#include "IRenderer.h"

template <typename RenderData>
class RendererBase : public IRenderer {
   public:
    RendererBase() = default;
    virtual ~RendererBase() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    virtual void Draw(const RenderData& data) = 0;

    // Engineで使われるためのエントリポイント
    void IDraw(const struct RenderDataBase& data) final {
        Draw(static_cast<const RenderData&>(data));
    }
};
