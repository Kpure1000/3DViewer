#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

/*********************/
/*  Light Properties */
uniform vec3 viewPos;
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    int shininess;
}; 
uniform Material _material;
struct Light {
    vec4 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light _light;
/*********************/

void getLightPara(out vec3 lightDir_out, out float attenuation_out)
{
    if(_light.position.w < 0.9) //  Directional lighta
    {
        lightDir_out = normalize(-_light.position.xyz);
        attenuation_out = 1.0;
    }
    else //  point light
    {
        vec3 lightDis=_light.position.xyz - FragPos;
        float distance = length(lightDis);
        lightDir_out = normalize(lightDis);
        attenuation_out = 1.0 / (_light.constant + _light.linear * distance
            + _light.quadratic * (distance * distance));
    }
}

vec3 diffuse(vec3 norm_para, vec3 lightDir_para)
{
    float diff = max(dot(norm_para, lightDir_para), 0.0);
    return _light.diffuse * diff * vec3(texture(_material.diffuse, TexCoord));
}

vec3 specular(vec3 norm_para, vec3 lightDir_para, vec3 viewDir_para)
{
    vec3 reflectDir = reflect(-lightDir_para, norm_para);  
    float spec = pow(max(dot(viewDir_para, reflectDir), 0.0), _material.shininess);
    return _light.specular * spec * vec3(texture(_material.specular, TexCoord));
}

void main()
{
    vec3 lightDir;
    float attenuation;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos-FragPos);

    getLightPara(lightDir, attenuation);
    
    vec3 result;

    float theta = dot(lightDir, normalize(-_light.direction));
    // Ambient
    vec3 ambient = _light.ambient * vec3(texture(_material.diffuse, TexCoord));
    //  Diffuse
    vec3 diffuse = diffuse(norm,lightDir);

    //  Specular
    vec3 specular = specular(norm, lightDir, viewDir);
    
    float epsilon = _light.cutOff - _light.outerCutOff;
    float intensity = clamp((theta - _light.outerCutOff) / epsilon, 0.0, 1.0);    
    result = attenuation * (ambient + intensity * (diffuse + specular));

    result += vec3(texture(_material.emission,TexCoord)); //  emission
    FragColor = vec4(result, 1.0);
}
