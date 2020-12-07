#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTexCoord;

out vec2 _texCoord;

uniform mat4 _transform;

void main()
{
    gl_Position = _transform * vec4(aPos, 1.0);
    _texCoord = aTexCoord;
}