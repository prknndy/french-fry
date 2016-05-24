#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec3 normal;

uniform mat4 gWVP;


void main()
{
    gl_Position = gWVP * vec4(position, 1.0);
}