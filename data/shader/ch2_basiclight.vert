#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

uniform vec3 _lightPos;

out vec3 _Normal;
out vec3 _Pos;
out vec3 _LightPos;

void main()
{
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);

    _Pos = vec3(_view * _model * vec4(aPos, 1.0));
    _Normal = normalize(mat3(transpose(inverse(_view * _model))) * aNormal);
    _LightPos = vec3(_view * vec4(_lightPos,1.0));
}