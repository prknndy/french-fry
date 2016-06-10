#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

uniform mat4 gWVP;
uniform mat4 gWorld;

out vec3 Color;
out vec2 Texcoord;
out vec3 Normal;
out vec3 WorldPos;

void main()
{
    gl_Position = gWVP * vec4(position, 1.0);
    Color = color;
    Texcoord = texcoord;
    Normal = normalize((gWorld * vec4(normal, 0.0)).xyz);
    WorldPos = (gWorld * vec4(position, 1.0)).xyz;
}
