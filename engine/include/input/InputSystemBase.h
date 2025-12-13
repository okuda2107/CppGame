#pragma once
#include <vector>

// 入力の状態を管理
/*
    InputComponent: Actorに入力情報を伝えるためのComponent
    InputState: 入力情報を格納
*/
template <typename InputState>
class InputSystemBase {
   protected:
    InputState mState;

   public:
    InputSystemBase() {}
    virtual ~InputSystemBase() {}

    virtual bool Initialize() = 0;
    virtual void Shutdown() = 0;

    // ポーリングではなく，イベントドリブンで入力状態を受け取る
    // virtual void ProcessEvent(SDL_Event& event) = 0;

    // 入力状態は前の状態からの変化を求められる場合もあるため，前処理で前の状態を保存する必要がある
    // SDL_PollEventsループの直前に呼ばれる
    virtual void PrepareForUpdate() = 0;
    // SDL_PollEventsループの直後に呼ばれる
    virtual void Update() = 0;

    const InputState& GetState() const { return mState; }
};
