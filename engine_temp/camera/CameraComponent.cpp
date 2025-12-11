#include "CameraComponent.h"

#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "audio/AudioSystemBase.h"
#include "audio/OpenAL/AudioComponent.h"
#include "audio/OpenAL/System.h"
#include "core/Math.h"

CameraComponent::CameraComponent(class Actor* owner, System* system,
                                 int updateOrder)
    : Component(owner, updateOrder) {
    mAudioComponent = OpenAL::AudioComponent(owner, system);
}

CameraComponent::~CameraComponent() {}

// viewをrendererとaudio systemに渡す．
void CameraComponent::SetViewMatrix(const class Matrix4& view) {
    Game* game = mOwner->GetGame();
    game->GetRenderer()->SetViewMatrix(view);
    mAudioComponent->GetSystem()->SetListener(view);
}
