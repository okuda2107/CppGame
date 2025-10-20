#version 420

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec2 flagTexCoord;

void main()
{
    gl_Position = vec4(inPosition, 1.0);
    flagTexCoord = inTexCoord;
}
