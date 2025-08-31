#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Shader.h"
#include "SkydomeComponent.h"
#include "SoundHandler.h"

class SkydomeTestActor : Actor {
   public:
    SkydomeTestActor(class Game* game) : Actor(game) {
        Actor* a = new Actor(game);
        SkydomeComponent* sc = new SkydomeComponent(a);
        a->SetScale(100.0);
        sc->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
        sc->SetShader(game->GetRenderer()->GetShader("Shaders/TestBox"));
    }
};
