#include "Actor.h"
#include "AudioComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "SoundHandler.h"

class TestActor : Actor {
    SoundHandler* handler;

   public:
    TestActor(class Game* game) : Actor(game) {
        this->SetPosition(Vector3(200, 100, 0));
        MeshComponent* mc = new MeshComponent(this);
        mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
        AudioComponent* ac = new AudioComponent(this);
        handler = ac->PlayEvent("bgm_main");
    };
    ~TestActor() {};

    void ActorInput(const uint8_t* keystate) {
        if (handler->IsValid()) {
            if (keystate[SDL_SCANCODE_S]) handler->Restart();
            if (keystate[SDL_SCANCODE_X]) handler->SetPaused(true);
            if (keystate[SDL_SCANCODE_C]) handler->SetPaused(false);
        }
        if (keystate[SDL_SCANCODE_A]) this->SetPosition(Vector3(200, -100, 0));
        if (keystate[SDL_SCANCODE_D]) this->SetPosition(Vector3(200, 100, 0));
    }
};
