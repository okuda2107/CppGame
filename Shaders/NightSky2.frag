#version 330 core
in vec3 vDir;  // 頂点シェーダから渡された方向ベクトル
out vec4 fragColor;

uniform vec3 uSkyColor;

void main() {
    vec3 dir = normalize(vDir);

    // 方向ベクトルを使って乱数を生成（座標→一意の乱数へ）
    float noise = fract(sin(dot(dir, vec3(12.9898, 78.233, 45.164))) * 43758.5453);

    // 星の出現確率を制御（0.999 以上なら星にする）
    float star = step(0.999, noise);

    // 星があれば白、なければ背景色
    vec3 color = mix(uSkyColor, vec3(1.0), star);

    fragColor = vec4(color, 1.0);
}
