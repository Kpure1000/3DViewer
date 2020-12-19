#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

in vec3 LightDir;

out vec4 FragColor;
/*********************/
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_diffuse4;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_normal;
    sampler2D texture_height;
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
    vec3 ambient = _light.ambient * vec3(texture(_material.texture_diffuse1, TexCoord));

    //  Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = LightDir;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = _light.diffuse * diff * vec3(mix(texture(_material.texture_diffuse1, TexCoord),
         texture(_material.texture_specular1, TexCoord), 0.5));

    //  Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), _material.shininess);
    vec3 specular = _light.specular * spec * vec3(texture(_material.texture_specular1, TexCoord));

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}

// #version 330 core
// out vec4 FragColor;

// in vec2 TexCoords;

// struct Material {
//     sampler2D texture_diffuse1;
//     sampler2D texture_diffuse2;
//     sampler2D texture_diffuse3;
//     sampler2D texture_diffuse4;
//     sampler2D texture_specular1;
//     sampler2D texture_specular2;
//     sampler2D texture_normal;
//     sampler2D texture_height;
//     sampler2D emission;
//     int shininess;
// }; 
// uniform Material _material;

// void main()
// {    
//     FragColor = mix(texture(_material.texture_diffuse1, TexCoords),
//         texture(_material.texture_specular1, TexCoords), 0.5);
// }