#pragma once
#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

class BonfireTestActor : Actor {
   public:
    BonfireTestActor(class Game* game) : Actor(game) {
        SetPosition(Vector3(100, 50, -50));
        SetScale(50.0);
        MeshComponent* mc = new MeshComponent(this);
        mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Bonfire.gpmesh"));
    }
};
