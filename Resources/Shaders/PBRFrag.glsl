#version 330

const int MAX_POINT_LIGHTS = 4;

const float PI = 3.14;

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
uniform float gRoughness;
uniform float gLinearRoughness;
uniform vec3 gF0;


// START PBR

//f0 = 0.16 * reflectance * reflectance
//f90 = 1?
vec3 F_Schlick(vec3 f0, float f90, float u)
{
    return f0 + (f90 - f0) * pow(1.0 - u, 5.0);
}

float GGX_V1(float m2, float NdotX)
{
    return 1.0 / (NdotX + sqrt(m2 + (1.0 - m2) * NdotX * NdotX));
}

float V_GGX(float NdotL, float NdotV, float m)
{
    float m2 = m * m;
    float v1i = GGX_V1(m2, NdotL);
    float v1o = GGX_V1(m2, NdotV);
    float vis = v1i * v1o;
    
    return vis;
}

float V_SmithGGXCorrelated(float NdotL, float NdotV, float alphaG)
{
    // Optimized version from Frostbite
    float alphaG2 = alphaG * alphaG;
    float Lambda_GGXV = NdotL * sqrt((-NdotV * alphaG2 + NdotV) * NdotV + alphaG2);
    float Lambda_GGXL = NdotV * sqrt((-NdotL * alphaG2 + NdotL) * NdotL + alphaG2);
    
    return 0.5 / (Lambda_GGXV + Lambda_GGXL);
}

float D_GGX(float NdotH, float m)
{
    float m2 = m * m;
    float f = (NdotH * m2 - NdotH) * NdotH + 1;
    return m2 / (f * f);
}

float Fr_DisneyDiffuse(float NdotV, float NdotL, float LdotH, float linearRoughness)
{
    float energyBias = mix(0, 0.5, linearRoughness);
    float energyFactor = mix(1.0, 1.0 / 1.51, linearRoughness);
    float fd90 = energyBias + 2.0 * LdotH * LdotH * linearRoughness;
    vec3 f0 = vec3(1.0, 1.0, 1.0);
    float lightScatter = F_Schlick(f0, fd90, NdotL).r;
    float viewScatter = F_Schlick(f0, fd90, NdotV).r;
    
    return lightScatter * viewScatter * energyFactor;
}

// roughness = 1.0f - smoothness, linear smoothness = (1 - smoothness)^4
vec3 Fr_Spec(float NdotV, float LdotH, float NdotH, float NdotL, vec3 f0, float roughness)
{
    // Spec
    vec3 F = F_Schlick(f0, 1.0, LdotH);
    float V = V_SmithGGXCorrelated(NdotL, NdotV, roughness);
    //float V = V_GGX(NdotL, NdotV, 0.0);
    float D = D_GGX(NdotH, roughness);
    vec3 Fr = D * F * V / PI;
    //Fr = Fr * 5.0;
    return Fr;
}

// END PBR
// float3 luminance = BSDF (...) * saturate ( dot (N , L)) * lightColor * att ;
// lighting = (diffuseAlbedo * InvPi + specular * fresnel) * nDotL * lightColor;
vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 WorldPos, vec3 N, vec3 diffuseAlbedo)
{
    vec3 Lighting = vec3(0, 0 , 0);
    
    vec3 L = -LightDirection;
    vec3 V = normalize(gEyeWorldPos - WorldPos);
    
    float NdotL = clamp(dot(N, L), 0.0, 1.0);
    
    if (NdotL > 0.0)
    {
        float NdotV = abs(dot(N, V));
        vec3 H = normalize(V + L);
        float LdotH = clamp(dot(L, H), 0.0, 1.0);
        float NdotH = clamp(dot(N, H), 0.0, 1.0);
        
        vec3 spec = Fr_Spec(NdotV, LdotH, NdotH, NdotL, gF0, gRoughness);
        //vec3 spec = vec3(0, 0 ,0);
        float diff = Fr_DisneyDiffuse(NdotV, NdotL, LdotH, gLinearRoughness) / PI;
        //float diff = 0.0;
        
        Lighting = (diffuseAlbedo * diff + spec) * NdotL * (Light.Color * Light.DiffuseIntensity);
        
        
        //Lighting = spec;
        
        Lighting = max(Lighting, 0);
    }
    
    return vec4(Lighting, 1.0);
}

vec4 CalcDirectionalLight(vec3 WorldPos, vec3 Normal, vec3 diffuseAlbedo)
{
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, WorldPos, Normal, diffuseAlbedo);
}

vec4 CalcPointLight(int index, vec3 WorldPos, vec3 Normal, vec3 diffuseAlbedo)
{
    vec3 LightDirection = WorldPos - gPointLight[index].Position;
    float Distance = length(LightDirection);
    
    vec4 color = CalcLightInternal(gPointLight[index].Base, LightDirection, WorldPos, Normal, diffuseAlbedo);
    
    float attenuation = gPointLight[index].Atten.Constant + gPointLight[index].Atten.Linear * Distance + gPointLight[index].Atten.Exp * Distance * Distance;
    
    return (color / attenuation);
}


out vec4 outColor;

void main()
{
    vec3 color = texture(tex, Texcoord).xyz * Color;
    vec4 light = vec4(color * vec3(0.0, 0.0, 0.0), 1.0);
    light += CalcDirectionalLight(WorldPos, Normal, color);
    for (int i = 0; i < gNumPointLights; i++)
    {
        light += CalcPointLight(i, WorldPos, Normal, color);
    }

    outColor = light;
    //outColor = vec4(color, 1.0);
}