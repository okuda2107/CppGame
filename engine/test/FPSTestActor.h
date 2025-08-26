#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "FPSComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"

class FPSTestActor : Actor {
   public:
    FPSTestActor(class Game* game) : Actor(game) {
        // 空間感を出すためのオブジェクト配置
        Actor* a = new Actor(GetGame());
        a->SetPosition(Vector3(100, -100, 0));
        MeshComponent* a_mc = new MeshComponent(a);
        a_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
        Actor* b = new Actor(GetGame());
        b->SetPosition(Vector3(100, 100, 0));
        MeshComponent* b_mc = new MeshComponent(b);
        b_mc->SetMesh(
            GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));

        this->SetPosition(Vector3(0, 0, 0));
        InputComponent* ic = new InputComponent(this);
        ic->SetMaxForwardSpeed(10);
        ic->SetMaxStrafeSpeed(10);
        ic->SetMaxYawSpeed(0.5);
        FPSComponent* fc = new FPSComponent(this);
        fc->SetMaxPitch(Math::Pi / 4);
        fc->SetInputPitchSpeed(0.5);
    };
    ~FPSTestActor() {};
};
