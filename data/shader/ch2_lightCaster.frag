#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;
/*********************/

uniform vec3 viewPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    int shininess;
}; 
uniform Material _material;

/*********************/
struct Light {
    vec4 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light _light;

/*********************/
void main()
{
    vec3 lightDir;
    float attenuation;
    if(_light.position.w < 0.9) //  Directional lighta
    {
        lightDir = normalize(-_light.position.xyz);
        attenuation=1.0;
    }
    else //  point light
    {
        vec3 lightDis=_light.position.xyz - FragPos;
        float distance = length(lightDis);
        attenuation = 1.0 / (_light.constant + _light.linear * distance
            + _light.quadratic * (distance * distance));
        lightDir = normalize(lightDis);
    }
    
    vec3 ambient = _light.ambient * vec3(texture(_material.diffuse, TexCoord));

    //  Diffuse
    vec3 norm = normalize(Normal);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * vec3(texture(_material.diffuse, TexCoord));

    //  Specular
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    vec3 specular = _light.specular * spec * vec3(texture(_material.specular, TexCoord));

    vec3 result = attenuation*(ambient + diffuse + specular) ;//+ vec3(texture(_material.emission,TexCoord));
    FragColor = vec4(result, 1.0);
}
