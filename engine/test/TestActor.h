#include "Actor.h"
#include "AudioComponent.h"
#include "FPSComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"

class TestActor : Actor {
   public:
    TestActor(class Game* game) : Actor(game) {
        // 空間感を出すためのオブジェクト配置
        Actor* a = new Actor(GetGame());
        a->SetPosition(Vector3(200, 0, 0));
        MeshComponent* a_mc = new MeshComponent(a);
        a_mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
        Actor* b = new Actor(GetGame());
        b->SetPosition(Vector3(200, 100, 0));
        MeshComponent* b_mc = new MeshComponent(b);
        b_mc->SetMesh(
            GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));

        this->SetPosition(Vector3(0, 0, 0));
        new InputComponent(this);
        new FPSComponent(this);
    };
    ~TestActor() {};
};
