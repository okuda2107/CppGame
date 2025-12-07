#include "CameraComponent.h"

#include "Actor.h"
#include "AudioSystem.h"
#include "Game.h"
#include "Renderer.h"
#include "core/Math.h"

CameraComponent::CameraComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {}

CameraComponent::~CameraComponent() {}

// viewをrendererとaudio systemに渡す．
void CameraComponent::SetViewMatrix(const class Matrix4& view) {
    Game* game = mOwner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
    game->GetAudioSystem()->SetListener(view);
}
