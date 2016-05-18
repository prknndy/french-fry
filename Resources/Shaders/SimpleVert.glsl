#version 150

in vec3 position;
in vec3 color;
in vec2 texcoord;

uniform mat4 gWVP;

out vec3 Color;
out vec2 Texcoord;

void main()
{
    gl_Position = gWVP * vec4(position, 1.0);
    Color = color;
    Texcoord = texcoord;
}