#version 330 core
out vec4 FragColor;

uniform vec3 _objectColor;
uniform vec3 _lightColor;

void main()
{
    vec3 result = _lightColor * _objectColor;

    FragColor = vec4(result, 1.0);
}