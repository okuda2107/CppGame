#pragma once
#include "Math.h"

struct Light {
    // 拡散反射光
    Vector3 mDiffuseColor;
    // 鏡面反射光
    Vector3 mSpecColor;
};

struct DirectionalLight : Light {
    // 光の方向
    Vector3 mDirection;
};

struct PointLight : Light {
    Vector3 mPosition;
    // 光の強さ
    float mIntensity;
};
