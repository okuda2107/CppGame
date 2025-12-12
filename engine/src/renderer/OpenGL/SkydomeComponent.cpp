#include "SkydomeComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

OpenGL::SkydomeComponent::SkydomeComponent(class Actor* owner, Renderer* system)
    : DrawComponentBase(owner, system),
      mMesh(nullptr),
      mShader(nullptr),
      mTextureIndex(0) {
    mSystem->AddSkydome(this);
}

OpenGL::SkydomeComponent::~SkydomeComponent() { mSystem->RemoveSkydome(); }

void OpenGL::SkydomeComponent::Draw(Matrix4 viewProj) {
    if (!mMesh || !mShader) return;
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
