#pragma once
#include "Component.h"
#include "core/Math.h"

class SkydomeComponent : public Component {
    class Mesh* mMesh;
    class Shader* mShader;
    size_t mTextureIndex;

   public:
    SkydomeComponent(class Actor* owner);
    ~SkydomeComponent();

    void Draw(Matrix4 viewProj);

    class Shader* GetShader() { return mShader; }

    void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void SetShader(class Shader* shader) { mShader = shader; }
    void SetTextureIndex(size_t index) { mTextureIndex = index; }
};
