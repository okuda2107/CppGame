#pragma once
#include "core/Math.h"
#include "renderer/DrawComponentBase.h"

namespace OpenGL {
class SkydomeComponent : public DrawComponentBase<class Renderer> {
    class Mesh* mMesh;
    class Shader* mShader;
    size_t mTextureIndex;

   public:
    SkydomeComponent(class Actor* owner, Renderer* system);
    ~SkydomeComponent();

    void Draw(Matrix4 viewProj);

    class Shader* GetShader() { return mShader; }

    void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void SetShader(class Shader* shader) { mShader = shader; }
    void SetTextureIndex(size_t index) { mTextureIndex = index; }
};
}  // namespace OpenGL
