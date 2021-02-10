#version 330 core

in vec3 inFragPos;
in vec2 inTexCoord;
in mat3 inTBN;

out vec4 FragColor;

//  -- uniform data -----------------------
//  -- the camera view position (eye)
uniform vec3 _eyePos;

//  --material data---------
//  -- material structure
struct Material {
    sampler2D diffuse;
    sampler2D normal;
    sampler2D specular;
    sampler2D emission;
    int shininess;
}; 
//  material data
uniform Material _material;
//  --light data------------
//  -- light structure
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
    //  direction of the spoting cone
    vec3 direction;
    //  inner cut off  
    float innerCutOff;
    //  outer cut off
    float outerCutOff;
};
//  max numbers of lights
#define MaxLightNumbers 20
//  lights data
uniform Light _lights[MaxLightNumbers];
//  real light count
uniform int _lightsNumber;

// -- function -----------------------

void lightInit_(Light param_light, out vec3 lightDir_out, out float attenuation_out)
{
    if(param_light.lightType == 0) //  Directional light
    {
        lightDir_out = inTBN * normalize(-param_light.position);
        attenuation_out = 1.0;
    }
    else //  Point light or Spot light
    {
        vec3 lightDis = param_light.position - inFragPos;
        float distance = length(lightDis);
        lightDir_out = inTBN * normalize(lightDis);
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
    //  -- direction of current light
    vec3 cur_light_dir;
    //  -- attenuation
    float attenuation;
    //  -- normal texture -- 
    vec3 normalRGB = texture(_material.normal, inTexCoord).rgb;
    //  -- normal
    vec3 norm = normalize(normalRGB * 2.0 - 1.0);
    //  -- direction of viewer' eyes
    vec3 eyeDir = inTBN * normalize(_eyePos - inFragPos);
    //  -- fragment output result
    vec3 result;
    
    //  -- traverse lights
    for(int i = 0; i < _lightsNumber && i < MaxLightNumbers; i++ )
    {
        //  -- initialize light parameter
        lightInit_(_lights[i], cur_light_dir, attenuation);

        //  -- Ambient
        vec3 ambient = _lights[i].ambient * vec3(texture(_material.diffuse, inTexCoord));

        //  -- Diffuse
        vec3 diffuse = diffuse_(_lights[i], norm, cur_light_dir);

        //  -- Specular
        vec3 specular = specular_(_lights[i], norm, cur_light_dir, eyeDir);
        
        //  -- Intensity
        float intensity = intensity_(_lights[i], cur_light_dir, _lights[i].direction);

        //  -- Result
        result += attenuation * (ambient + intensity * (diffuse + specular));
    }

    //  -- Emission
    // result += texture(_material.emission, inTexCoord).rgb;

    FragColor = vec4(result, 1.0);
}
