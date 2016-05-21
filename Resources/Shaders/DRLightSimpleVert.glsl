#version 330

in vec3 position;
in vec3 color;
in vec2 texcoord;
in vec3 normal;

uniform mat4 gWVP;
uniform mat4 gWorld;


void main()
{
    gl_Position = gWVP * vec4(position, 1.0);
}