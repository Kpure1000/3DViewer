#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCooord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 inFragPos;
out vec3 inNormal;
out vec2 inTexCoord;
out mat3 inTBN;

uniform mat4 _model;
uniform mat4 _view;
uniform mat4 _projection;

void main()
{
    vec3 T = normalize(vec3(_model * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(_model * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(_model * vec4(aNormal, 0.0)));
    inTBN = transpose(mat3(T, B, N));

    inFragPos = vec3(_model * vec4(aPos, 1.0));
    inTexCoord = aTexCooord;
    inNormal = aNormal;
    gl_Position = _projection * _view * _model * vec4(aPos, 1.0);

}