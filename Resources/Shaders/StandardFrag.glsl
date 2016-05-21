#version 330

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

in vec3 Color;
in vec2 Texcoord;
in vec3 Normal;
in vec3 WorldPos;

uniform sampler2D tex;

uniform DirectionalLight gDirectionalLight;
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

out vec4 outColor;

void main()
{
    vec3 color = texture(tex, Texcoord).xyz * Color;
    outColor = vec4(Color, 1.0) * CalcDirectionalLight(WorldPos, Normal);
}