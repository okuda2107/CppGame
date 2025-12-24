#pragma once
#include "Actor.h"
#include "AudioComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "SoundHandler.h"

class AudioTestActor : Actor {
    AudioComponent* ac;

    Matrix4 mView;

    bool prevS = false;

   public:
    AudioTestActor(class Game* game) : Actor(game) {
        this->SetPosition(Vector3(200, 100, 0));
        MeshComponent* mc = new MeshComponent(this);
        mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
        ac = new AudioComponent(this);
        ac->RegisterEvent("bgm_main");
        mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX,
                                      Vector3::UnitZ);
        GetGame()->GetAudioSystem()->SetListener(mView);
    };
    ~AudioTestActor() {};

    void ActorInput(const uint8_t* keystate) {
        SoundHandler* handler = ac->GetEvent("bgm_main");
        if (handler) {
            if (keystate[SDL_SCANCODE_S] && !prevS) handler->Restart();
            prevS = keystate[SDL_SCANCODE_S];
            if (keystate[SDL_SCANCODE_X]) handler->SetPaused(true);
            if (keystate[SDL_SCANCODE_C]) handler->SetPaused(false);
        }
        if (keystate[SDL_SCANCODE_A]) this->SetPosition(Vector3(200, -100, 0));
        if (keystate[SDL_SCANCODE_D]) this->SetPosition(Vector3(200, 100, 0));
    }
};
