#include "SpriteComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "core/Math.h"

OpenGL::SpriteComponent::SpriteComponent(class Actor* owner, Renderer* system,
                                         int drawOrder)
    : DrawComponentBase(owner, system, drawOrder = drawOrder),
      mTexHeight(128),
      mTexWidth(128),
      mTexture(nullptr) {
    mSystem->AddSprite(this);
}

OpenGL::SpriteComponent::~SpriteComponent() { mSystem->RemoveSprite(this); }

void OpenGL::SpriteComponent::Draw(Shader* shader) {
    Matrix4 scaleMat = Matrix4::CreateScale(
        static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
    Matrix4 world = scaleMat * mOwner->GetWorldTransform();

    shader->SetMatrixUniform("uWorldTransform", world);

    mTexture->SetActive();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGL::SpriteComponent::SetTexture(Texture* tex) {
    mTexture = tex;
    mTexWidth = tex->GetWidth();
    mTexHeight = tex->GetHeight();
}
