#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uSceneTex;
uniform float uBlurStrength = 3.0; // 例: 1.0〜3.0

void main()
{
    vec2 texelSize = 1.0 / textureSize(uSceneTex, 0);
    vec3 color = texture(uSceneTex, TexCoord).rgb * 0.4;
    color += texture(uSceneTex, TexCoord + vec2(texelSize.x * uBlurStrength, 0)).rgb * 0.15;
    color += texture(uSceneTex, TexCoord - vec2(texelSize.x * uBlurStrength, 0)).rgb * 0.15;
    color += texture(uSceneTex, TexCoord + vec2(0, texelSize.y * uBlurStrength)).rgb * 0.15;
    color += texture(uSceneTex, TexCoord - vec2(0, texelSize.y * uBlurStrength)).rgb * 0.15;

    FragColor = vec4(color, 1.0);
}
