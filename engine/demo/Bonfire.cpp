#include "Bonfire.h"

#include "AnimMeshComponent.h"
#include "AudioComponent.h"
#include "BonfirePlayer.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"

Bonfire::Bonfire(class Game* game)
    : Actor(game),
      mTime(0.0f),
      mLimit(0.0f),
      cMaxLimit(10.0f),
      mIsRunning(false),
      mFinished(false),
      mAddWood(false),
      mPlayer(nullptr) {
    SetPosition(Vector3(100, 50, -50));
    SetScale(100.0);
    RenderConfig config = RenderConfig();
    config.mBlend = true;
    config.mDepthMask = false;
    config.mSortByCamera = true;
    AnimMeshComponent* mc = new AnimMeshComponent(this, config);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Bonfire.gpmesh"));

    AudioComponent* ac = new AudioComponent(this);
    ac->RegisterEvent("takibi");
    mEvent = ac->GetEvent("takibi");
    if (!mEvent) {
        SDL_Log("failed to get sound event");
    } else {
        mEvent->Restart();
    }

    mLimit = cMaxLimit;
}

// todo: 時間で消える処理を書く
void Bonfire::UpdateActor(float deltatime) {
    if (!mIsRunning) return;
    // 時間更新
    mTime += deltatime;
    mLimit -= deltatime;
    if (mLimit <= 0) {
        mFinished = true;
        return;
    }

    SetScale(mLimit / cMaxLimit * 100.0f);
    // 音声処理
    mEvent->SetVolume(mLimit / cMaxLimit);

    // Playerが近くにいる かつ flagが送られたら，時間延長
    float dx = mPlayer->GetPosition().x - GetPosition().x;
    float dy = mPlayer->GetPosition().y - GetPosition().y;
    float d = Vector2(dx, dy).LengthSquared();
    float near = 5000.0f;
    if (d < near && mAddWood) {
        mAddWood = false;
        mLimit += 20;
    }
}
