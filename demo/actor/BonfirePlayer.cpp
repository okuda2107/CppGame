#include "BonfirePlayer.h"

#include "Bonfire.h"
#include "UI/AddWoodUI.h"
#include "UI/AlreadyHaveWoodUI.h"
#include "UI/HaveWoodUI.h"
#include "Utility/Coroutine.h"
#include "Wood.h"
#include "WoodGenerator.h"
#include "core/Math.h"
#include "input/InputSystem.h"

BonfirePlayer::BonfirePlayer(class ActorsSystem* system, BonfirePlayerDeps deps)
    : FPSActor(system, deps),
      mIsAnimLookUp(false),
      mIsAnimLookDown(false),
      mLookUpEndTime(-1.0f),
      mLookDownEndTime(-1.0f),
      mHasWood(false),
      mWoodUI(nullptr),
      mBonfireUI(nullptr),
      mGenerator(nullptr),
      mBonfireID(0),
      mActorsSystem(deps.actorsSystem) {
    mCoroutines = new Coroutine();
    mGenerator = new WoodGenerator(GetGame());
    cc = new ContextComponent<Bonfire>(this);
}

BonfirePlayer::~BonfirePlayer() {
    delete mCoroutines;
    mGenerator->SetState(Actor::State::EDead);
    if (mWoodUI && mWoodUI->GetState() != UIScreen::EClosing) mWoodUI->Close();
    if (mBonfireUI && mBonfireUI->GetState() != UIScreen::EClosing)
        mBonfireUI->Close();
}

void BonfirePlayer::ActorInput(const InputState& state) {
    // アニメーション中は操作を受け付けない
    if (mIsAnimLookUp || mIsAnimLookDown) return;
    FPSActor::ActorInput(state);

    // 木が近くにあるとき，Eキーを押すと拾う
    // 既に持っている場合は拾えない
    for (auto& wood : mGenerator->GetWoods()) {
        float dx = wood->GetPosition().x - GetPosition().x;
        float dy = wood->GetPosition().y - GetPosition().y;
        float d = Vector2(dx, dy).LengthSquared();
        float near = 5000.0f;
        if (d < near && state.Keyboard->GetKeyState(SDL_SCANCODE_E)) {
            if (!mHasWood) {
                mHasWood = true;
                wood->SetState(Actor::State::EDead);
                break;
            } else {
                new AlreadyHaveWoodUI(GetGame());
            }
        }
    }

    // Bonfireが近くにある時，Eキーを押すと木をくべられる
    auto bonfire = mActorsSystem.GetActor<Bonfire>(mBonfireID);
    if (bonfire != nullptr && mHasWood) {
        float dx = bonfire->GetPosition().x - GetPosition().x;
        float dy = bonfire->GetPosition().y - GetPosition().y;
        float d = Vector2(dx, dy).LengthSquared();
        float near = 5000.0f;
        if (d < near && state.Keyboard.GetKeyState(SDL_SCANCODE_E)) {
            mHasWood = false;
            bonfire->AddWood();
        }
    }
}

void BonfirePlayer::Initialize() { mGenerator->SetRunning(); }

void BonfirePlayer::UpdateActor(float deltatime) {
    mCoroutines->Update(deltatime);
    if (mIsAnimLookUp) {
        if (mLookUpEndTime < 0)
            mLookUpEndTime = mCoroutines->AddCoroutine(
                2.0, [this](float t) { this->PitchUp(t); });
        if (mCoroutines->CheckCoroutine(mLookUpEndTime)) {
            mIsAnimLookUp = false;
            mLookUpEndTime = -1.0f;
        }
    } else if (mIsAnimLookDown) {
        if (mLookDownEndTime < 0)
            mLookDownEndTime = mCoroutines->AddCoroutine(
                2.0, [this](float t) { this->PitchDown(t); });
        if (mCoroutines->CheckCoroutine(mLookDownEndTime)) {
            mIsAnimLookDown = false;
            mLookDownEndTime = -1.0f;
        }
    }
    FPSActor::UpdateActor(deltatime);

    // 位置の制限
    Vector3 pos = GetPosition();
    pos.x = Math::Clamp(pos.x, mFieldMin.x, mFieldMax.x);
    pos.y = Math::Clamp(pos.y, mFieldMin.x, mFieldMax.y);
    SetPosition(pos);

    // 木が近くにある時，UIを出す制御
    bool isNear = false;
    for (auto& wood : mGenerator->GetWoods()) {
        float dx = wood->GetPosition().x - GetPosition().x;
        float dy = wood->GetPosition().y - GetPosition().y;
        float d = Vector2(dx, dy).LengthSquared();
        float near = 5000.0f;
        isNear = d < near;
        if (isNear) break;
    }
    if (!mWoodUI && isNear) {
        mWoodUI = new HaveWoodUI(GetGame());
    } else if (mWoodUI && !isNear) {
        mWoodUI->Close();
        mWoodUI = nullptr;
    }

    // Bonfireが近くにある時，UIを出す制御
    auto bonfire = cc->GetActor();
    if (bonfire) {
        float dx = bonfire->GetPosition().x - GetPosition().x;
        float dy = bonfire->GetPosition().y - GetPosition().y;
        float d = Vector2(dx, dy).LengthSquared();
        float near = 5000.0f;
        if (!mBonfireUI && d < near && mHasWood) {
            mBonfireUI = new AddWoodUI(GetGame());
        } else if (mBonfireUI && (d >= near || !mHasWood)) {
            mBonfireUI->Close();
            mBonfireUI = nullptr;
        }
    }
}

float BonfirePlayer::Ease(float t) { return 0.5f * (1 - cosf(Math::Pi * t)); }

// カメラの視線を下げる
void BonfirePlayer::PitchDown(float lerp) {
    float t = Ease(lerp);
    SetPitchAngular(Math::Lerp(-Math::Pi / 4, 0, t));
}

// カメラの視線を上げる
void BonfirePlayer::PitchUp(float lerp) {
    float t = Ease(lerp);
    SetPitchAngular(Math::Lerp(0, -Math::Pi / 4, t));
}
