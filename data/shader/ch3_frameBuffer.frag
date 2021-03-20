#version 330 core

in vec3 inFragPos;
in vec2 inTexCoord;

out vec4 FragColor;

uniform sampler2D _tx;

void main()
{
    FragColor = texture(_tx, inTexCoord);
}