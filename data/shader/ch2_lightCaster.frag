#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightDir;
in vec2 TexCoord;

out vec4 FragColor;
/*********************/
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    int shininess;
}; 
uniform Material _material;

/*********************/
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light _light;

/*********************/
void main()
{
    vec3 ambient = _light.ambient  * vec3(texture(_material.diffuse, TexCoord));

    // 漫反射 
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(LightPos - FragPos);
    vec3 lightDir = -LightDir;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * vec3(texture(_material.diffuse, TexCoord));

    // 镜面光
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    vec3 specular = _light.specular * spec * vec3(texture(_material.specular, TexCoord));

    vec3 result = ambient + diffuse + specular + vec3(texture(_material.emission,TexCoord));
    FragColor = vec4(result, 1.0);
}
