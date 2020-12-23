#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCooord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform vec4 _lightLocate;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

void main()
{
    FragPos = vec3(_model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(_model))) * aNormal;
    TexCoord = aTexCooord;
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);
}