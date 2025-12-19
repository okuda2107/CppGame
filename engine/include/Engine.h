#pragma once
#include "core/base/CoreBase.h"
#include "core/base/GameBase.h"
#include "input/base/InputSystemBase.h"
#include "renderer/base/RendererBase.h"

// 入力，更新，出力の連携を責務とする
template <typename InputState, typename RenderData>
class Engine {
   public:
    CoreBase* mCore;
    // game内部の世界を表現
    GameBase<InputState, RenderData>* mGame;
    // 入力情報処理を責務とする
    InputSystemBase<InputState>* mInputSystem;
    // 画面表示処理を責務とする
    RendererBase* mRenderer;

    void RunLoop() {
        while (mCore->IsGameLoop()) {
            mInputSystem->Update();
            mGame->ProcessInput(mInputSystem->GetState());
            mGame->Update(mCore->CalculateDeltatime());
            mRenderer->Draw(mGame->GenerateRenderData());
        }
    }
};
