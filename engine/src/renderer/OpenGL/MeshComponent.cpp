#include "renderer/OpenGL/MeshComponent.h"

#include <algorithm>

#include "core/Actor.h"
#include "renderer/OpenGL/Mesh.h"
#include "renderer/OpenGL/Renderer.h"
#include "renderer/OpenGL/Shader.h"
#include "renderer/OpenGL/Texture.h"
#include "renderer/OpenGL/VertexArray.h"

MeshComponent::MeshComponent(Actor* owner, class RenderDB* database,
                             RenderConfig config)
    : Component(owner), mMesh(nullptr) {
    ConfigID id = mSystem->GetConfigID(config);
    mConfigID = id;
    mSystem->AddMeshComp(id, this);
}

OpenGL::MeshComponent::~MeshComponent() {
    mSystem->RemoveMeshComp(mConfigID, this);
}

void OpenGL::MeshComponent::Draw(const std::string& shaderName,
                                 Shader* shader) {
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

// void OpenGL::MeshComponent::LoadProperties(const rapidjson::Value& inObj) {
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

void OpenGL::MeshComponent::AddTextureIndex(size_t index) {
    mTextureIndices.push_back(index);
}

void OpenGL::MeshComponent::RemoveTextureIndex(size_t index) {
    auto iter =
        std::find(mTextureIndices.begin(), mTextureIndices.end(), index);
    if (iter != mTextureIndices.end()) {
        mTextureIndices.erase(iter);
    }
}
