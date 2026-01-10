#include "Bonfire.h"

#include "BonfirePlayer.h"
#include "game/audio/AudioComponent.h"
#include "game/object/ActorsSystem.h"
#include "game/physics/SphereComponent.h"
#include "renderer/AnimMeshComponent.h"
#include "renderer/Mesh.h"
#include "renderer/RenderDB.h"

Bonfire::Bonfire(ActorsSystem* system, BonfireDeps& deps)
    : Actor(system, deps),
      mTime(0.0f),
      mLimit(0.0f),
      cMaxLimit(30.0f),
      mIsRunning(false),
      mFinished(false),
      mAddWood(false),
      mPlayerID(0),
      mActorsSystem(*system) {
    SetPosition(Vector3(100, 50, -50));
    SetScale(100.0);
    AnimMeshComponent* mc = new AnimMeshComponent(this, &deps.renderDB,
                                                  RenderConfigID::Translucent);
    mc->SetMesh(deps.renderDB.GetMesh("Assets/Bonfire.gpmesh"));

    AudioComponent* ac = new AudioComponent(this, deps.audioSystem);
    ac->RegisterEvent("takibi");
    mEvent = ac->GetEvent("takibi");
    mEvent.Restart();

    mLimit = cMaxLimit;

    SphereComponent* sphereComp = new SphereComponent(
        this, SBonfirePhysTag.data(), CollisionCompDeps(deps.physWorld));
    // todo: Sphereの半径を調整
    Sphere sphere{};
    sphere.mCenter = GetPosition();
    sphere.mRadius = 2500.0f;
    sphereComp->mSphere = sphere;
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
    mEvent.SetVolume(mLimit / cMaxLimit);

    // Playerが近くにいる かつ flagが送られたら，時間延長
    class BonfirePlayer* player =
        mActorsSystem.GetActor<BonfirePlayer>(mPlayerID);
    if (player) {
        float dx = player->GetPosition().x - GetPosition().x;
        float dy = player->GetPosition().y - GetPosition().y;
        float d = Vector2(dx, dy).LengthSquared();
        float near = 5000.0f;
        if (d < near && mAddWood) {
            mAddWood = false;
            mLimit += 20;
            if (mLimit > cMaxLimit + 30) mLimit = cMaxLimit + 30;
        }
    }
}
