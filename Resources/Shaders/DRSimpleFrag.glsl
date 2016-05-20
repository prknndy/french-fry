#version 330

in vec3 Color;
in vec2 Texcoord;
in vec3 Normal;
in vec3 WorldPos;

uniform sampler2D tex;

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 TexCoordOut;

void main()
{
    WorldPosOut = WorldPos;
    DiffuseOut = texture(tex, Texcoord).xyz * Color;
    NormalOut = normalize(Normal);
    TexCoordOut = vec3(Texcoord, 0.0);
}