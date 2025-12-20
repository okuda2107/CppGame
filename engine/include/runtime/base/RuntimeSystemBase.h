#pragma once

// ゲームプログラムの実行環境，フレーム，時間処理を責務とする
template <typename GameData>
class RuntimeSystemBase {
   protected:
    float mDeltatime;

   public:
    RuntimeSystemBase() {}
    virtual ~RuntimeSystemBase() {}

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    // gameの更新を続行するか
    virtual bool IsRunning() = 0;

    // フレームの開始，終了を明示
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;

    // gameから送られてくるデータを基に処理する
    // ex. ゲームループの継続判定など
    virtual void ProcessGameData(const GameData& data) = 0;

    // deltatimeを提供する
    float GetDeltatime() { return mDeltatime; };
};
