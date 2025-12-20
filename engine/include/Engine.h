#pragma once
#include "game/base/GameBase.h"
#include "input/base/InputSystemBase.h"
#include "renderer/base/RendererBase.h"
#include "runtime/base/RuntimeSystemBase.h"

// 入力，更新，出力の連携を責務とする
template <typename InputState, typename RenderData, typename GameData>
class Engine {
   public:
    // game内部の世界を表現
    GameBase<InputState, RenderData, GameData>* mGame;
    // 入力情報処理を責務とする
    InputSystemBase<InputState>* mInputSystem;
    // 画面表示処理を責務とする
    RendererBase<RenderData>* mRenderer;

    RuntimeSystemBase<GameData>* mRuntimeSystem;

    void RunLoop() {
        while (mRuntimeSystem->IsRunning()) {
            mRuntimeSystem->BeginFrame();
            mInputSystem->Update();
            mGame->ProcessInput(mInputSystem->GetState());
            const GameData& gameData =
                mGame->Update(mRuntimeSystem->GetDeltatime());
            mRenderer->Draw(mGame->GenerateRenderData());
            mRuntimeSystem->EndFrame();
            mRuntimeSystem->ProcessGameData(gameData);
        }
    }
};
