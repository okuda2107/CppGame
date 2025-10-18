#include "Bonfire.h"

#include "AnimMeshComponent.h"
#include "AudioComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"

Bonfire::Bonfire(class Game* game) : Actor(game) {
    SetPosition(Vector3(100, 50, -50));
    SetScale(50.0);
    RenderConfig config = RenderConfig();
    config.mBlend = true;
    config.mDepthMask = false;
    config.mSortByCamera = true;
    AnimMeshComponent* mc = new AnimMeshComponent(this, config);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Bonfire.gpmesh"));

    AudioComponent* ac = new AudioComponent(this);
    ac->RegisterEvent("takibi");
    SoundHandler* e = ac->GetEvent("takibi");
    if (!e) {
        SDL_Log("failed to get sound event");
    } else {
        e->Restart();
    }
}
