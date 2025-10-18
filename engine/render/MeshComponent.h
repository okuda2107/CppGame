#pragma once
#include "Component.h"
#include "LevelLoader.h"
#include "Renderer.h"

class MeshComponent : public Component {
   public:
    MeshComponent(class Actor* owner, struct RenderConfig config);
    ~MeshComponent();
    // Draw this mesh component
    virtual void Draw(const std::string& shaderName, class Shader* shader);
    // Set the mesh/texture index used by mesh component
    virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void AddTextureIndex(size_t index);
    void RemoveTextureIndex(size_t index);

    // void LoadProperties(const rapidjson::Value& inObj) override;

   protected:
    class Mesh* mMesh;
    ConfigID mConfigID;
    // このmeshで用いるテクスチャ群
    std::vector<size_t> mTextureIndices;
};
