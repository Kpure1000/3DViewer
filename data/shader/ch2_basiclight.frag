// #version 330 core
// out vec4 FragColor;

// uniform vec3 _objectColor;
// uniform vec3 _lightColor;

// uniform float _ambientStrength;
// uniform float _specularStrength;
// uniform int _gloss;

// in vec3 Normal;
// in vec3 FragPos;
// in vec3 LightPos;

// void main()
// {
//     float ambientStrength = _ambientStrength;
//     vec3 ambient = ambientStrength * _lightColor;

//     vec3 lightDir = LightPos - FragPos;
//     vec3 diffuse = _lightColor * max(0.0, dot(Normal, lightDir));

//     float specularStrength = _specularStrength;
//     int gloss = _gloss;
//     vec3 viewDir = normalize(-FragPos);
//     vec3 reflectDir = reflect(-lightDir, Normal);
//     vec3 specular = specularStrength * _lightColor * pow(max(dot(viewDir, reflectDir), 0.0), gloss);

//     vec3 result = (ambient + diffuse + specular) * _objectColor;
//     // vec3 result = (ambient + diffuse) * _objectColor;
//     // vec3 result = diffuse * _objectColor;

//     FragColor = vec4(result, 1.0);
// }

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;    
    
     // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}