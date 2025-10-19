#pragma once
#include <string>

#include "glew.h"

class RenderPath {
    class Renderer* mRenderer;

    std::string mShaderName;

    unsigned int mBuffer;
    unsigned int mColorBuffer;
    unsigned int mDepthBuffer;

   public:
    RenderPath(class Renderer* renderer, std::string effectName);
    ~RenderPath();

    bool Load();
    void Unload();

    // このFBOを描画対象に設定
    void SetActive();

    // スクリーン（デフォルトFBO）に結果をコピー or 描画
    void BlitToScreen();
};
