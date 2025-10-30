#pragma once
#include <string>
#include <vector>

#include "glew.h"

// エフェクトを適用できるレンダリングパイプラインを定義
// 一つのレンダリングバッファを持ち，効果を適用する．
class RenderPath {
    class Renderer* mRenderer;

    std::vector<class Shader*> mEffects;

    unsigned int mBuffer;
    unsigned int mColorBuffer;
    unsigned int mDepthBuffer;

    unsigned int mTempBuffer;
    unsigned int mTempColorBuffer;

   public:
    RenderPath(class Renderer* renderer);
    ~RenderPath();

    bool Load();
    void Unload();

    void AddEffect(class Shader* shader);

    // このFBOを描画対象に設定
    void SetActive();

    // 効果をテクスチャに適用
    void ApplyEffect(class VertexArray* va);

    unsigned int GetTextureIndex() { return mColorBuffer; }
};
