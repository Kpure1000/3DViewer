#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec2 TexCoords;

out vec4 FragColor;
/*********************/
struct Material {
    sampler2D diffuse;
    vec3 specular;
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
    // 环境光
    vec3 ambient = _light.ambient * _material.ambient;

    // 漫反射 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * texture(_material.diffuse,);

    // 镜面光
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    vec3 specular = _light.specular * (spec * _material.specular);  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
