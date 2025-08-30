#include "SkydomeComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

SkydomeComponent::SkydomeComponent(class Actor* owner)
    : Component(owner), mMesh(nullptr), mShader(nullptr), mTextureIndex(0) {
    mOwner->GetGame()->GetRenderer()->AddSkydome(this);
}

SkydomeComponent::~SkydomeComponent() {
    mOwner->GetGame()->GetRenderer()->RemoveSkydome();
}

void SkydomeComponent::Draw(Matrix4 viewProj) {
    if (mMesh || mShader) return;
    mShader->SetActive();
    mShader->SetMatrixUniform("uViewProj", viewProj);
    mShader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
    Texture* t = mMesh->GetTexture(mTextureIndex);
    if (t) {
        t->SetActive();
    }
    VertexArray* va = mMesh->GetVertexArray();
    va->SetActive();
    // Draw
    glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}
