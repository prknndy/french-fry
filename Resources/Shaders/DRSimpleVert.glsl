#version 330

in vec3 position;
in vec3 color;
in vec2 texcoord;
in vec3 normal;

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
    Normal = (gWorld * vec4(normal, 0.0)).xyz;
    WorldPos = (gWorld * vec4(position, 1.0)).xyz;
}