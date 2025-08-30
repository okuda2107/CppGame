#version 330
in vec3 TexCoords;
out vec4 FragColor;

float hash(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

void main() {
    // 球のUV座標から緯度経度を計算
    vec2 uv = vec2(
        atan(TexCoords.z, TexCoords.x) / (2.0 * 3.14159) + 0.5,
        acos(TexCoords.y) / 3.14159
    );

    // 擬似乱数で星の有無を判定
    float noise = hash(floor(uv * 500.0)); // 密度調整
    float brightness = step(0.995, noise) * (0.5 + noise * 0.5);

    vec3 color = vec3(brightness); // 白い星
    FragColor = vec4(color, 1.0);
}
