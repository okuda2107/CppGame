#version 420
in vec2 TexCoord;
out vec4 FragColor;

layout(binding=0) uniform sampler2D uSceneTex;
uniform float uBlurStrength = 3.0; // 例: 1.0〜3.0

void main()
{
    FragColor = texture(uSceneTex, TexCoord);
}
