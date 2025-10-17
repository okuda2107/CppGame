#include "BackDome.h"

#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "SkydomeComponent.h"

BackDome::BackDome(class Game* game) : Actor(game), mTime(0.0f) {
    SetScale(100.0);
    sc = new SkydomeComponent(this);
    sc->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    sc->SetShader(game->GetRenderer()->GetShader("Shaders/NightSky"));
}

void BackDome::UpdateActor(float deltatime) {
    mTime += deltatime;
    sc->GetShader()->SetActive();
    sc->GetShader()->SetFloatUniform("uTime", mTime);
}
