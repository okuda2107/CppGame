#pragma once

// ゲームの内部での処理定義を責務とする
template <typename InputState, typename RenderData, typename GameData,
          typename GameMetrics>
class GameBase {
   protected:
   public:
    GameBase() = default;
    virtual ~GameBase() = default;

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    // 入力を処理
    virtual void ProcessInput(const InputState& state) = 0;
    // deltatimeに基づいてgameを更新する
    // GameDataは更新結果を外部に伝達したいときのコンテナ
    virtual const GameData& Update(float deltatime,
                                   const GameMetrics& metrics) = 0;
    // gameの出力を生成
    virtual const RenderData& GenerateRenderData() = 0;
};
