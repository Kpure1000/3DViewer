#version 330 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;

out vec4 FragColor;

/*********************/
/*  Light Properties */
//  the camera view position (eye)
uniform vec3 _eyePos;

/*material structure*/
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    int shininess;
}; 
//  material
uniform Material _material;
/*light structure*/
struct Light {
    //  type of light
    int lightType; 
    
    //  position of light source
    vec3 position;  
    
    //  normal light attribute
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    //  point based light param
    float constant;
    float linear;
    float quadratic;
    
    //  spot light special param
    vec3 direction;         //  direction of the spoting cone
    float innerCutOff;      //  inner cut off  
    float outerCutOff;      //  outer cut off
};
//  max numbers of lights
#define MaxLightNumbers 20
//  lights data
uniform Light _lights[MaxLightNumbers];
//  real light count
uniform int _lightsNumber;

/*********************/

void lightInit_(Light param_light, out vec3 lightDir_out, out float attenuation_out)
{
    if(param_light.lightType == 0) //  Directional light
    {
        lightDir_out = normalize(-param_light.position);
        attenuation_out = 1.0;
    }
    else //  Point light or Spot light
    {
        vec3 lightDis = param_light.position - inFragPos;
        float distance = length(lightDis);
        lightDir_out = normalize(lightDis);
        attenuation_out = 1.0 / (param_light.constant + param_light.linear * distance
            + param_light.quadratic * (distance * distance));
    }
}

vec3 diffuse_(Light param_light, vec3 norm_para, vec3 lightDir_para)
{
    float diff = max(dot(norm_para, lightDir_para), 0.0);
    return param_light.diffuse * diff * vec3(texture(_material.diffuse, inTexCoord));
}

vec3 specular_(Light param_light, vec3 norm_para, vec3 lightDir_para, vec3 viewDir_para)
{
    vec3 reflectDir = reflect(-lightDir_para, norm_para);  
    float spec = pow(max(dot(viewDir_para, reflectDir), 0.0), _material.shininess);
    return param_light.specular * spec * vec3(texture(_material.specular, inTexCoord));
}

float intensity_(Light param_light, vec3 curDir,vec3 spotDir)
{
    if(param_light.lightType == 2) //  spot light
    {
        float theta = dot(curDir, normalize(-spotDir));
        return clamp((theta - param_light.outerCutOff) 
            / (param_light.innerCutOff - param_light.outerCutOff), 0.0, 1.0);
    }
    else 
    {
        return 1.0f;
    }
}
void NormalColor(inout vec3 Color)
{
    Color.x = min(1.0, max(0.0, Color.x));
    Color.y = min(1.0, max(0.0, Color.y));
    Color.z = min(1.0, max(0.0, Color.z));
}
void main()
{
    vec3 cur_light_dir;
    float attenuation;
    vec3 norm = normalize(inNormal); 
    vec3 eyeDir = normalize(_eyePos - inFragPos);
    vec3 result;
    
    for(int i = 0; i < _lightsNumber && i < MaxLightNumbers; i++ )
    {
        lightInit_(_lights[i],cur_light_dir, attenuation);

        // Ambient
        vec3 ambient = _lights[i].ambient * vec3(texture(_material.diffuse, inTexCoord));

        //  Diffuse
        vec3 diffuse = diffuse_(_lights[i], norm,cur_light_dir);

        //  Specular
        vec3 specular = specular_(_lights[i], norm, cur_light_dir, eyeDir);
        
        //  Intensity
        float intensity = intensity_(_lights[i], cur_light_dir,_lights[i].direction);

        //  Result
        result += attenuation * (ambient + intensity * (diffuse + specular));
    }

    // result += vec3(texture(_material.emission, inTexCoord)); //  emission

    FragColor = vec4(result, 1.0);
}
