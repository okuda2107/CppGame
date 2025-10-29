#include "Floor.h"

#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

Floor::Floor(class Game* game) : Actor(game) {
    SetPosition(Vector3(0, 0, -70));
    SetScale(10.0);
    RenderConfig config = RenderConfig();
    // config.effectName = "Shaders/PostEffectBlur";
    MeshComponent* mc = new MeshComponent(this, config);
    mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
    mc->AddTextureIndex(0);
}
