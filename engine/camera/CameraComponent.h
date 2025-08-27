#pragma once
#include "Component.h"

// ゲームオブジェクトに関連付けられたカメラ
class CameraComponent : public Component {
   protected:
    void SetViewMatrix(const class Matrix4& view);

   public:
    CameraComponent(class Actor* owner, int drawOrder = 200);
    ~CameraComponent();
};
