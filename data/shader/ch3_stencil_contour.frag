#version 330 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.8, 0.45, 0.26, 1.0);
}