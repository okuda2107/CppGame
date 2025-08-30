#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "FPSActor.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "SkydomeComponent.h"
#include "SoundHandler.h"

class SkydomeTestActor : FPSActor {
   public:
    SkydomeTestActor(class Game* game) : FPSActor(game) {
        Actor* a = new Actor(game);
        SkydomeComponent* sc = new SkydomeComponent(a);
        sc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
        sc->SetShader(game->GetRenderer()->GetShader("Shaders/Basic"));
    }
};
