#version 330

const int MAX_POINT_LIGHTS = 4;

struct BaseLight
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
};

struct DirectionalLight
{
    BaseLight Base;
    vec3 Direction;
};

struct Attenuation
{
    float Constant;
    float Linear;
    float Exp;
};

struct PointLight
{
    BaseLight Base;
    Attenuation Atten;
    vec3 Position;
};

in vec3 Color;
in vec2 Texcoord;
in vec3 Normal;
in vec3 WorldPos;

uniform sampler2D tex;

uniform int gNumPointLights;
uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLight[MAX_POINT_LIGHTS];
uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity;
uniform float gMatSpecularPower;

vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 WorldPos, vec3 Normal)
{
    vec4 AmbientColor = vec4(Light.Color * Light.AmbientIntensity, 1.0);
    float DiffuseFactor = dot(Normal, -LightDirection);
    
    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0 ,0);
    
    if (DiffuseFactor > 0.0)
    {
        DiffuseColor = vec4(Light.Color * Light.DiffuseIntensity * DiffuseFactor, 1.0);
        
        vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos);
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
        float SpecularFactor = dot(VertexToEye, LightReflect);
        if (SpecularFactor > 0.0)
        {
            SpecularFactor = pow(SpecularFactor, gMatSpecularPower);
            SpecularColor = vec4(Light.Color * gMatSpecularIntensity * SpecularFactor, 1.0);
        }
    }
    
    return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcDirectionalLight(vec3 WorldPos, vec3 Normal)
{
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, WorldPos, Normal);
}

vec4 CalcPointLight(int index, vec3 WorldPos, vec3 Normal)
{
    vec3 LightDirection = WorldPos - gPointLight[index].Position;
    float Distance = length(LightDirection);
    
    vec4 color = CalcLightInternal(gPointLight[index].Base, LightDirection, WorldPos, Normal);
    
    float attenuation = gPointLight[index].Atten.Constant + gPointLight[index].Atten.Linear * Distance + gPointLight[index].Atten.Exp * Distance * Distance;
    
    return (color / attenuation);
}

out vec4 outColor;

void main()
{
    vec3 color = texture(tex, Texcoord).xyz * Color;
    
    vec4 light = CalcDirectionalLight(WorldPos, Normal);
    for (int i = 0; i < gNumPointLights; i++)
    {
        light += CalcPointLight(i, WorldPos, Normal);
    }

    outColor = vec4(color, 1.0) * light;
}