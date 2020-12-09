#version 330 core
out vec4 FragColor;

uniform vec3 _objectColor;
uniform vec3 _lightColor;

uniform float _ambientStrength;
uniform float _specularStrength;
uniform int _gloss;

in vec3 _Normal;
in vec3 _Pos;
in vec3 _LightPos;

void main()
{
    float ambientStrength = _ambientStrength;
    vec3 ambient = ambientStrength * _lightColor;

    vec3 lightDir = _LightPos - _Pos;
    vec3 diffuse = _lightColor * max(0.0, dot(_Normal, lightDir));

    float specularStrength = _specularStrength;
    int gloss = _gloss;
    vec3 viewDir = normalize(-_Pos);
    vec3 reflectDir = reflect(-lightDir, _Normal);
    vec3 specular = specularStrength * _lightColor * pow(max(dot(viewDir, reflectDir), 0.0), gloss);

    vec3 result = (ambient + diffuse + specular) * _objectColor;

    FragColor = vec4(result, 1.0);
}