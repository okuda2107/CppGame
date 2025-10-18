#include "Floor.h"

#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

Floor::Floor(class Game* game) : Actor(game) {
    SetPosition(Vector3(0, 0, -70));
    SetScale(10.0);
    MeshComponent* mc =
        new MeshComponent(this, RenderConfig(false, false, true, true));
    mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
    mc->AddTextureIndex(0);
}
