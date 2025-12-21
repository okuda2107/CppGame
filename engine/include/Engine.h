#pragma once
#include "game/base/GameBase.h"
#include "game/base/IGame.h"
#include "input/base/IInputSystem.h"
#include "input/base/InputSystemBase.h"
#include "renderer/base/IRenderer.h"
#include "renderer/base/RendererBase.h"
#include "runtime/base/IRuntimeSystem.h"
#include "runtime/base/RuntimeSystemBase.h"

// 入力，更新，出力の連携を責務とする
// systemの初期化，終了処理は処理していない．
// 現状の実装は，必要ならばゲーム実装者側で処理する必要がある．
class Engine {
    // game内部の世界を表現
    class IGame* mGame;
    // 入力情報処理を責務とする
    class IInputSystem* mInputSystem;
    // gameの世界を表示することを責務とする
    class IRenderer* mRenderer;

    class IRuntimeSystem* mRuntimeSystem;

   public:
    // 型指定の正当性を保証するためのsetter
    template <typename InputState, typename RenderData, typename GameData,
              typename Metrics>
    void SetSystem(class GameBase<InputState, RenderData, GameData,
                                  typename Metrics::Game>* game,
                   class InputSystemBase<InputState>* inputSystem,
                   class RendererBase<RenderData>* renderer,
                   class RuntimeSystemBase<GameData, Metrics>* runtimeSystem) {
        mGame = game;
        mInputSystem = inputSystem;
        mRenderer = renderer;
        mRuntimeSystem = runtimeSystem;
    }

    void RunLoop() {
        while (mRuntimeSystem->IIsRunning()) {
            // frameの開始
            mRuntimeSystem->IBeginFrame();

            // 入力処理
            mInputSystem->IUpdate();
            mGame->IProcessInput(mInputSystem->IGetState());

            // game更新
            const GameDataBase& gameData =
                mGame->IUpdate(mRuntimeSystem->IGetDeltatime(),
                               mRuntimeSystem->IGetGameMetrics());

            // 画面出力
            mRenderer->IDraw(mGame->IGenerateRenderData());

            // runtimeの更新，情報の集計など
            mRuntimeSystem->IProcessGameData(gameData);

            // frameの終了
            mRuntimeSystem->IEndFrame();
        }
    }
};
