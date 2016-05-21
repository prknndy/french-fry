#version 330

uniform sampler2D gPositionMap;
uniform sampler2D gColorMap;
uniform sampler2D gNormalMap;

uniform vec2 gScreenSize;

vec2 CalcTexCoord()
{
    return gl_FragCoord.xy / gScreenSize;
}

out vec4 outColor;

void main()
{
    vec2 TexCoord = CalcTexCoord();
    vec2 ModTexCoord = vec2(TexCoord.x, TexCoord.y);
    
    vec3 WorldPos = texture(gPositionMap, ModTexCoord).xyz;
    vec3 Color = texture(gColorMap, TexCoord).xyz;
    vec3 Normal = texture(gNormalMap, TexCoord).xyz;
    Normal = normalize(Normal);
    
    //outColor = vec4(Color, 1.0) * CalcDirectionalLight(WorldPos, Normal);
    //vec4 toutColor = vec4(Color, 1.0) * CalcDirectionalLight(WorldPos, Normal);
    outColor = vec4(Color, 1.0);
}