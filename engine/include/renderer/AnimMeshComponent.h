#pragma once
#include "MeshComponent.h"

class AnimMeshComponent : public MeshComponent {
    float mTime;

   public:
    AnimMeshComponent(class Actor* owner, Renderer* system,
                      class RenderConfig config);
    ~AnimMeshComponent();

    void Update(float deltatime) override { mTime += deltatime; }
    void Draw(const std::string& shaderName, Shader* shader) override;
};
