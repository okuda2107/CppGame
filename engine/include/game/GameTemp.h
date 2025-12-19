#pragma once
#include "audio/base/AudioSystemBase.h"
#include "core/base/GameBase.h"
#include "input/base/InputSystemBase.h"
#include "object/base/ObjectsSystemBase.h"
#include "renderer/base/RendererBase.h"

template <typename InputState, typename SoundHandler>
class Game {
   protected:
    //入力を処理
    void ProcessInput() {
        mInputSystem->Update();
        mObjectsSystem->ProcessInput(mInputSystem->GetState());
    }

    // deltatimeに基づいてgameを更新する
    void UpdateGame(float deltatime) {
        mAudioSystem->Update();
        mObjectsSystem->UpdateObjects(deltatime);
    }

    // gameの出力を生成
    void GenerateOutput() { mRenderer->Draw(); }

    GameBase* mCore;
    ObjectsSystemBase<InputState>* mObjectsSystem;
    InputSystemBase<InputState>* mInputSystem;
    RendererBase* mRenderer;

    AudioSystemBase<SoundHandler>* mAudioSystem;

    UISystem* mUISystem;

   public:
    bool Initialize() {}

    void RunLoop() {
        while (mCore->IsGameLoop()) {
            ProcessInput();
            UpdateGame(mCore->CalculateDeltatime());
            GenerateOutput();
        }
    }

    void Shutdown() {}
};
