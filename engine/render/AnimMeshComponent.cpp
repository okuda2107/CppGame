#include "AnimMeshComponent.h"

#include "Mesh.h"

AnimMeshComponent::AnimMeshComponent(class Actor* owner,
                                     class RenderConfig* config)
    : MeshComponent(owner, config), mTime(0.0f) {}

AnimMeshComponent::~AnimMeshComponent() {}

void AnimMeshComponent::Draw(const std::string& shaderName, Shader* shader) {
    mTextureIndices.clear();
    size_t size = mMesh->GetTextureArraySize();
    size_t index = static_cast<size_t>(size * mTime) % size;
    mTextureIndices.push_back(index);
    MeshComponent::Draw(shaderName, shader);
}
