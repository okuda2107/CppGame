#pragma once
#include <unordered_map>
#include <vector>

#include "core/Math.h"

template <typename Texture, typename Mesh, typename Shader,
          typename SpriteComponent, typename MeshComponent>
class RendererBase {
   protected:
    std::unordered_map<std::string, Texture*> mTextures;
    std::unordered_map<std::string, Mesh*> mMeshes;
    std::unordered_map<std::string, Shader*> mShaders;
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

    Texture* GetTexture(const std::string& filename);
    Mesh* GetMesh(const std::string& filename);
    Shader* GetShader(const std::string& shaderName);

    virtual void Draw() = 0;
};
