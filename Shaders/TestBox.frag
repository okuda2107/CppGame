#version 330 core

in vec3 vTexCoord;
out vec4 outColor;

// サンプラー
uniform samplerCube uSkybox;

void main()
{
    // サンプルテクスチャはキューブマップ
    outColor = vec4(0.0, 0.0, 1.0, 1.0);
}
