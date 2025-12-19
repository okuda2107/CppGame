#pragma once

// ゲームのループに関わる情報の処理をカプセル化
class CoreBase {
   public:
    CoreBase() {}
    virtual ~CoreBase() {}

    virtual bool Initialize() { return true; }
    virtual void Shutdown() {}

    // gameの更新を続行するか
    virtual bool IsGameLoop() = 0;

    // deltatimeを計算する
    virtual float CalculateDeltatime() = 0;
};
