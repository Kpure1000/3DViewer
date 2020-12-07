#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec2 aTexCoord;

out vec2 _texCoord;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

void main()
{
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);
    _texCoord = aTexCoord;
}