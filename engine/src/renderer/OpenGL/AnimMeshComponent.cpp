#include "renderer/OpenGL/AnimMeshComponent.h"

#include "renderer/OpenGL/Mesh.h"

OpenGL::AnimMeshComponent::AnimMeshComponent(class Actor* owner,
                                             Renderer* system,
                                             class RenderConfig config)
    : MeshComponent(owner, system, config), mTime(0.0f) {}

OpenGL::AnimMeshComponent::~AnimMeshComponent() {}

void OpenGL::AnimMeshComponent::Draw(const std::string& shaderName,
                                     Shader* shader) {
    mTextureIndices.clear();
    size_t size = mMesh->GetTextureArraySize();
    size_t index = static_cast<size_t>(size * mTime) % size;
    mTextureIndices.push_back(index);
    MeshComponent::Draw(shaderName, shader);
}
