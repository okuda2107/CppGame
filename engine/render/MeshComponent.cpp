#include "MeshComponent.h"

#include <algorithm>

#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* owner, RenderConfig config)
    : Component(owner), mMesh(nullptr) {
    ConfigID id = mOwner->GetGame()->GetRenderer()->GetConfigID(config);
    mConfigID = id;
    mOwner->GetGame()->GetRenderer()->AddMeshComp(id, this);
}

MeshComponent::~MeshComponent() {
    mOwner->GetGame()->GetRenderer()->RemoveMeshComp(mConfigID, this);
}

void MeshComponent::Draw(const std::string& shaderName, Shader* shader) {
    if (mMesh) {
        if (mMesh->GetShaderName() != shaderName) return;
        // Set the world transform
        //そのオブジェクト特有のパラメータを用いる場合ここに書く
        shader->SetMatrixUniform("uWorldTransform",
                                 mOwner->GetWorldTransform());
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        // Set the active texture
        for (size_t i = 0; i < mTextureIndices.size(); i++) {
            Texture* t = mMesh->GetTexture(mTextureIndices[i]);
            if (t) {
                t->SetActive(i);
            }
        }
        // Set the mesh's vertex array as active
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        // Draw
        glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT,
                       nullptr);
    }
}

// void MeshComponent::LoadProperties(const rapidjson::Value& inObj) {
//     Component::LoadProperties(inObj);

//     std::string meshFile;
//     if (JsonHelper::GetString(inObj, "meshFile", meshFile)) {
//         SetMesh(mOwner->GetGame()->GetRenderer()->GetMesh(meshFile));
//     }

//     int idx;
//     if (JsonHelper::GetInt(inObj, "textureIndex", idx)) {
//         mTextureIndex = static_cast<size_t>(idx);
//     }
// }

void MeshComponent::AddTextureIndex(size_t index) {
    mTextureIndices.push_back(index);
}

void MeshComponent::RemoveTextureIndex(size_t index) {
    auto iter =
        std::find(mTextureIndices.begin(), mTextureIndices.end(), index);
    if (iter != mTextureIndices.end()) {
        mTextureIndices.erase(iter);
    }
}
