#pragma once
#include <unordered_map>
#include <vector>

#include "core/Math.h"

class RendererBase {
   protected:
    Matrix4 mView;
    Matrix4 mProjection;

   public:
    RendererBase() {}
    virtual ~RendererBase() {}

    virtual bool Initialize(float screenWidth, float screenHeight) = 0;
    virtual void Shutdown() = 0;

    virtual void Draw() = 0;
};
