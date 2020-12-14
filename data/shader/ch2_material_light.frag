#version 330 core

uniform vec3 _LightColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(_LightColor,1.0);
}