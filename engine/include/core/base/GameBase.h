#pragma once

// ゲームプログラムにおける処理の順序などを保証する基底クラス
class GameBase {
   protected:
    // gameの更新を続行するか
    virtual bool IsGameLoop() = 0;

    // 入力を処理
    virtual void ProcessInput() = 0;
    // deltatimeを計算する
    virtual float CalculateDeltatime() = 0;
    // deltatimeに基づいてgameを更新する
    virtual void UpdateGame(float deltatime) = 0;
    // gameの出力を生成
    virtual void GenerateOutput() = 0;

   public:
    GameBase() {}
    virtual ~GameBase() {}

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    void RunLoop();
};
