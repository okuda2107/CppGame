#include "Wood.h"

#include "Game.h"
#include "MeshComponent.h"
#include "WoodGenerator.h"

Wood::Wood(class Game* game, class WoodGenerator* parent)
    : Actor(game), mTime(0.0f), mParent(parent) {
    RenderConfig config = RenderConfig();
    config.mBlend = true;
    config.mDepthMask = false;
    config.mSortByCamera = true;
    MeshComponent* mc = new MeshComponent(this, config);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Square.gpmesh"));
    mc->AddTextureIndex(0);
    parent->AddWood(this);
    SetScale(30.0f);
}

Wood::~Wood() { mParent->RemoveWood(this); }

void Wood::UpdateActor(float deltatime) {
    mTime += deltatime;
    // くるくる回転するアニメーション
    Quaternion q = Quaternion(Vector3::UnitZ, mTime / 5 * Math::TwoPi);
    SetRotation(q);
}
