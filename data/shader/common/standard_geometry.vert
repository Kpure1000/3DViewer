#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCooord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out vec3 LightDir;

// if locate->w < 1, it's a direct light
uniform vec4 _lightLocate;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

void main()
{
    FragPos = vec3(_view * _model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(_view * _model))) * aNormal;
    TexCoord = aTexCooord;
    
    if(_lightLocate.w < 0.9)
    {
        LightDir = normalize(-_lightLocate.xyz);
    }
    else
    {
        LightDir = normalize(vec3(_view * vec4(_lightLocate.xyz,1.0)) - FragPos);
    }

    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);
}