#include "Bonfire.h"

#include "AnimMeshComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"

Bonfire::Bonfire(class Game* game) : Actor(game) {
    SetPosition(Vector3(100, 50, -50));
    SetScale(50.0);
    RenderConfig config;
    config.mBlend = true;
    config.mCullFaceBack = false;
    config.mDepthMask = false;
    config.mDepthTest = true;
    AnimMeshComponent* mc = new AnimMeshComponent(this, &config);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Bonfire.gpmesh"));
}
