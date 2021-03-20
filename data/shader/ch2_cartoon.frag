#version 330 core

in vec3 inFragPos;
in vec3 inNormal;
in vec2 inTexCoord;
in mat3 inTBN;

out vec4 FragColor;

//  -- uniform data -----------------------
//  -- the camera view position (eye)
uniform vec3 _eyePos;
uniform vec4 _DiffuseSegment;
uniform float _SpecularSegment;
//  --material data---------
//  -- material structure
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
        // lightDir_out = inTBN * normalize(-param_light.position);
        lightDir_out = normalize(-param_light.position);
        attenuation_out = 1.0;
    }
    else //  Point light or Spot light
    {
        vec3 lightDis = param_light.position - inFragPos;
        float distance = length(lightDis);
        // lightDir_out = inTBN * normalize(lightDis);
        lightDir_out = normalize(lightDis);
        attenuation_out = 1.0 / (param_light.constant + param_light.linear * distance
            + param_light.quadratic * (distance * distance));
    }
}

vec3 diffuse_(Light param_light, vec3 norm_para, vec3 lightDir_para)
{
    float diff = max(dot(norm_para, lightDir_para), 0.0);
    float w = fwidth(diff) * 2.0;
    if (diff < _DiffuseSegment.x + w) {
        diff = clamp (_DiffuseSegment.x, _DiffuseSegment.y, smoothstep(_DiffuseSegment.x - w, _DiffuseSegment.x + w, diff));
    //  diff = clamp(_DiffuseSegment.x, _DiffuseSegment.y, clamp(0.5 * (diff - _DiffuseSegment.x) / w, 0, 1));
    } else if (diff < _DiffuseSegment.y + w) {
        diff = clamp(_DiffuseSegment.y, _DiffuseSegment.z, smoothstep(_DiffuseSegment.y - w, _DiffuseSegment.y + w, diff));
    //  diff = clamp(_DiffuseSegment.y, _DiffuseSegment.z, clamp(0.5 * (diff - _DiffuseSegment.y) / w, 0, 1));
    } else if (diff < _DiffuseSegment.z + w) {
        diff = clamp(_DiffuseSegment.z, _DiffuseSegment.w, smoothstep(_DiffuseSegment.z - w, _DiffuseSegment.z + w, diff));
    //  diff = clamp(_DiffuseSegment.z, _DiffuseSegment.w, clamp(0.5 * (diff - _DiffuseSegment.z) / w, 0, 1));
    } else {
        diff = _DiffuseSegment.w;
    }
    return param_light.diffuse * diff * vec3(texture(_material.texture_diffuse1, inTexCoord));
}

vec3 specular_(Light param_light, vec3 norm_para, vec3 lightDir_para, vec3 viewDir_para)
{
    vec3 reflectDir = reflect(-lightDir_para, norm_para);  
    float spec = pow(max(dot(viewDir_para, reflectDir), 0.0), _material.shininess);
    float w = fwidth(spec);
    if (spec < _SpecularSegment + w) {
        // spec = clamp(0, 1, smoothstep(_SpecularSegment - w, _SpecularSegment + w, spec));
        spec = 0;
    } else {
        spec = 1;
    }
    return param_light.specular * spec * vec3(texture(_material.texture_specular1, inTexCoord));
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
    vec3 normalRGB = texture(_material.texture_normal, inTexCoord).rgb;
    //  -- normal
    vec3 norm = normalize(inNormal);// normalize(normalRGB * 2.0 - 1.0);
    //  -- direction of viewer' eyes
    // vec3 eyeDir = inTBN * normalize(_eyePos - inFragPos);
    vec3 eyeDir = normalize(_eyePos - inFragPos);
    //  -- fragment output result
    vec3 result;
    
    //  -- traverse lights
    for(int i = 0; i < _lightsNumber && i < MaxLightNumbers; i++ )
    {
        //  -- initialize light parameter
        lightInit_(_lights[i], cur_light_dir, attenuation);

        //  -- Ambient
        vec3 ambient = vec3(0);// _lights[i].ambient * vec3(texture(_material.texture_diffuse1, inTexCoord));

        //  -- Diffuse
        vec3 diffuse = diffuse_(_lights[i], norm, cur_light_dir);

        //  -- Specular
        vec3 specular = 1.0 * specular_(_lights[i], norm, cur_light_dir, eyeDir);
        
        //  -- Intensity
        float intensity = intensity_(_lights[i], cur_light_dir, _lights[i].direction);

        //  -- Result
        // attenuation=1.0;
        result += attenuation * (ambient + intensity * (diffuse + specular));
    }

    //  -- Emission
    // result += texture(_material.emission, inTexCoord).rgb;

    FragColor = vec4(result, pow(0.48, 2.2));
    // FragColor = vec4(texture(_material.texture_diffuse1, inTexCoord));
}
