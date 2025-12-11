#include "renderer/RendererBase.h"

#define RENDERER_BASE_TEMPLATE                                  \
    template <typename Texture, typename Mesh, typename Shader, \
              typename SpriteComponent, typename MeshComponent>
#define RENDERER_BASE \
    RendererBase<Texture, Mesh, Shader, SpriteComponent, MeshComponent>

RENDERER_BASE_TEMPLATE
Texture* RENDERER_BASE::GetTexture(const std::string& filename) {
    Texture* tex = nullptr;
    auto iter = mTextures.find(filename);
    if (iter != mTextures.end()) {
        tex = iter->second;
    } else {
        tex = new Texture();
        if (tex->Load(filename)) {
            mTextures.emplace(filename, tex);
        } else {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

RENDERER_BASE_TEMPLATE
Mesh* RendererBase<Texture, Mesh, Shader, SpriteComponent,
                   MeshComponent>::GetMesh(const std::string& filename) {
    Mesh* m = nullptr;
    auto iter = mMeshes.find(fileName);
    if (iter != mMeshes.end()) {
        m = iter->second;
    } else {
        m = new Mesh();
        if (m->Load(fileName, this)) {
            mMeshes.emplace(fileName, m);
        } else {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

RENDERER_BASE_TEMPLATE
Shader* RENDERER_BASE::GetShader(const std::string& shaderName) {
    Shader* m = nullptr;
    auto iter = mShaders.find(shaderName);
    if (iter != mShaders.end()) {
        m = iter->second;
    } else {
        m = new Shader();
        if (m->Load(shaderName + ".vert", shaderName + ".frag")) {
            mShaders.emplace(shaderName, m);
        } else {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

#undef RENDERER_BASE_TEMPLATE
#undef RENDERER_BASE
