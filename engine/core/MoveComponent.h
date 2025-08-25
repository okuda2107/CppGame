#pragma once
#include "Component.h"
#include "Math.h"
#include "document.h"

class MoveComponent : public Component {
    // 相対空間
    float mForwardSpeed;
    float mRightSpeed;
    float mUpSpeed;
    // 振り向き角速度
    float mYawSpeed;
    float mPitchSpeed;
    float mRollSpeed;

    // 絶対空間
    float mXSpeed;
    float mYSpeed;
    float mZSpeed;
    // 振り向き角速度
    float mXAngularSpeed;
    float mYAngularSpeed;
    float mZAngularSpeed;

    // ownerのpositonを変更する補助関数
    void SetOwnerPosition(const class Vector3& direction, float speed,
                          float deltatime);
    // ownerのrotationを変更する補助関数
    void SetOwnerRotation(const class Vector3& axis, float speed,
                          float deltatime);

   public:
    MoveComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltatime);

    void SetForwardSpeed(float forwardSpeed) { mForwardSpeed = forwardSpeed; }
    void SetRightSpeed(float rightSpeed) { mRightSpeed = rightSpeed; }
    void SetUpSpeed(float upSpeed) { mUpSpeed = upSpeed; }
    void SetYawSpeed(float yawSpeed) { mYawSpeed = yawSpeed; }
    void SetPitchSpeed(float pitchSpeed) { mPitchSpeed = pitchSpeed; }
    void SetRollSpeed(float rollSpeed) { mRollSpeed = rollSpeed; }

    void SetXSpeed(float xSpeed) { mXSpeed = xSpeed; }
    void SetYSpeed(float ySpeed) { mYSpeed = ySpeed; }
    void SetZSpeed(float zSpeed) { mZSpeed = zSpeed; }
    void SetXAngularSpeed(float xAngularSpeed) {
        mXAngularSpeed = xAngularSpeed;
    }
    void SetYAngularSpeed(float yAngularSpeed) {
        mYAngularSpeed = yAngularSpeed;
    }
    void SetZAngularSpeed(float zAngularSpeed) {
        mZAngularSpeed = zAngularSpeed;
    }

    TypeID GetType() const { return TypeID::TMoveComponent; }

    void LoadProperties(const rapidjson::Value& inObj) override;
};
