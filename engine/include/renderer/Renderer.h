#pragma once
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

#include "SDL.h"
#include "base/RendererBase.h"
#include "core/Math.h"

struct DirectionalLight {
    // 光の方向
    Vector3 mDirection;
    // 拡散反射光
    Vector3 mDiffuseColor;
    // 鏡面反射光
    Vector3 mSpecColor;
};

// 将来的に描画設定を個別に設定できるようにする
struct RenderConfig {
    bool mDepthTest;
    bool mDepthMask;
    bool mBlend;
    bool mCullFaceBack;
    bool mSortByCamera;
    int mOrder = 100;  // 設定別の描画優先順位
    // 一般的な不透明オブジェクトをデフォルト値とする
    RenderConfig()
        : mBlend(false),
          mCullFaceBack(false),
          mDepthMask(true),
          mDepthTest(true),
          mSortByCamera(false) {}
};

// 将来的にハッシュ値になる可能性
// 現在はここで順序を設定
enum ConfigID {
    Dome = 0,
    Opaque,
    Translucent,
    NUM_CONFIG_ID,
};

class Renderer : public RendererBase {
   public:
    Renderer(class UISystem* system);
    ~Renderer();
    // レンダラーの初期化処理と終了処理
    bool Initialize(float screenWidth, float screenHeight);
    void Shutdown();
    // 全てのテクスチャ・メッシュを解放
    void UnloadData();
    // フレームの描画
    void Draw();

    // SDL_Windowは不完全型
    class SDL_Window* GetWindow() const { return mWindow; }

    // order順に比較できるhashを返す
    ConfigID GetConfigID(const RenderConfig& config);

    // 与えられた描画設定を適用する / 解除する
    void ApplyConfig(const ConfigID id);
    void ResetConfig();

   private:
    bool LoadShaders();
    void CreateSpriteVerts();
    void SetLightUniforms(class Shader* shader);
    // これは本来Shader.hファイルに書くべき？ <-
    // 3D表示するときにしか使わんからRendererファイルでいいかも
    // このファイルに新しく光源の配列作っても良し
    // 光の計算はシェーダーにとっては必要不可欠ではない

    class UISystem* mUISystem;

    class Shader* mSpriteShader;
    class VertexArray* mSpriteVerts;

    Matrix4 mProjection;

    float mScreenWidth;
    float mScreenHeight;

    SDL_Window* mWindow;
    SDL_GLContext mContext;
};
