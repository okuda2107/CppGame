#pragma once
#include <unordered_map>
#include <vector>

#include "core/Math.h"

template <typename SpriteComponent, typename MeshComponent>
class RendererBase {
   protected:
    std::vector<SpriteComponent*> mSprites;
    std::vector<MeshComponent*> mMeshComps;

    Matrix4 mView;
    Matrix4 mProjection;

    float mScreenWidth;
    float mScreenHeight;

   public:
    RendererBase() {}
    virtual ~RendererBase() {}

    virtual bool Initialize(float screenWidth, float screenHeight) = 0;
    virtual void Shutdown() = 0;

    virtual void Draw() = 0;
};
