#pragma once
#include "game/base/GameBase.h"
#include "input/base/InputSystemBase.h"
#include "renderer/base/RendererBase.h"
#include "runtime/base/RuntimeSystemBase.h"

// 入力，更新，出力の連携を責務とする
template <typename InputState, typename RenderData, typename GameData,
          typename Metrics>
class Engine {
   public:
    // game内部の世界を表現
    GameBase<InputState, RenderData, GameData, typename Metrics::Game>* mGame;
    // 入力情報処理を責務とする
    InputSystemBase<InputState>* mInputSystem;
    // gameの世界を表示することを責務とする
    RendererBase<RenderData, typename Metrics::Renderer>* mRenderer;

    RuntimeSystemBase<GameData, Metrics>* mRuntimeSystem;

    void RunLoop() {
        while (mRuntimeSystem->IsRunning()) {
            // frameの開始
            mRuntimeSystem->BeginFrame();

            // 入力処理
            mInputSystem->Update();
            mGame->ProcessInput(mInputSystem->GetState());

            // game更新
            const GameData& gameData =
                mGame->Update(mRuntimeSystem->GetDeltatime(),
                              mRuntimeSystem->GetGameMetrics());

            // 画面出力
            mRenderer->Draw(mGame->GenerateRenderData());

            // runtimeの更新，情報の集計など
            mRuntimeSystem->ProcessGameData(gameData);

            // frameの終了
            mRuntimeSystem->EndFrame();
        }
    }
};
