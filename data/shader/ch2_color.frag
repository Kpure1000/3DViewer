#version 330 core
out vec4 FragColor;

uniform vec3 _objectColor;
uniform vec3 _lightColor;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * _lightColor;

    vec3 result = ambient * _objectColor;

    FragColor = vec4(result, 1.0);
}