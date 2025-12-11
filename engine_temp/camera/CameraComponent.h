#pragma once
#include "Component.h"

namespace OpenAL {
class AudioComponent;
}

// ゲームオブジェクトに関連付けられたカメラ
class CameraComponent : public Component {
   protected:
    OpenAL::AudioComponent* mAudioComponent;

    void SetViewMatrix(const class Matrix4& view);

   public:
    CameraComponent(class Actor* owner, class System* system,
                    int drawOrder = 200);
    ~CameraComponent();
};
