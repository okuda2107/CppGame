#pragma once
#include <unordered_map>

#include "RenderData.h"

class RenderDB {
    RenderData mData;

    // assetの管理
    std::unordered_map<std::string, class Texture*> mTextures;
    std::unordered_map<std::string, class Mesh*> mMeshes;
    std::unordered_map<std::string, class Shader*> mShaders;
    std::unordered_map<std::string, class Font*> mFonts;

   public:
    const RenderData& GetData() { return mData; }

    void UnloadAssets();

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    void AddMeshComp(const ConfigID config, class MeshComponent* mesh);
    void RemoveMeshComp(const ConfigID config, class MeshComponent* mesh);

    void AddSkydome(class SkydomeComponent* skydome) {
        mData.mSkydome = skydome;
    }
    void RemoveSkydome() { mData.mSkydome = nullptr; }

    void SetViewMatrix(const class Matrix4& view) { mData.mView = view; }

    void SetAmbientLight(const Vector3& ambient) {
        mData.mAmbientLight = ambient;
    }  // 全体に一つしかないのでRendererに書く
    DirectionalLight& GetDirectionalLight() { return mData.mDirLight; }

    class Texture* GetTexture(const std::string& fileName);
    class Mesh* GetMesh(const std::string& fileName);
    class Shader* GetShader(const std::string& shaderName);
    class Font* GetFont(const std::string& fileName);
};
