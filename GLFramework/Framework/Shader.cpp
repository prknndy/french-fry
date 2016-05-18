//
//  Shader.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include <stdio.h>

#include "Shader.h"
#include "Util.h"
#include "Renderer.h"

bool Shader::CompileShader(const char* vertFilename, const char* fragFilename)
{
    GLint status;
    //char * buffer = LoadFile(vertFilename);
    
    string buffer;
    if (!ReadFile(vertFilename, buffer))
    {
       fputs ("Failed to read vertex shader\n",stderr);
    }
    // Load vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    const GLchar* p[1];
    p[0] = buffer.c_str();
    
    glShaderSource(vertexShader, 1, p, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char compilelog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, compilelog);
        fputs (compilelog,stderr);
        fputs ("Failed to compile vertex shader\n",stderr);
        return false;
    }
    
    // Load fragment shader
    string buffer2;
    if (!ReadFile(fragFilename, buffer2))
    {
        fputs ("Failed to read fragment shader\n",stderr);
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const GLchar* p2[1];
    p2[0] = buffer2.c_str();
    
    glShaderSource(fragmentShader, 1, p2, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
        fputs (buffer,stderr);
        fputs ("Failed to compile fragment shader\n",stderr);
        return false;
    }
    
    
    // Assemble shader
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    
    glLinkProgram(shaderProgram);
    
    return true;
}

bool Shader::CreateShader(const char* vertFilename, const char* fragFilename)
{
    if (!CompileShader(vertFilename, fragFilename))
    {
        return false;
    }
    
    WVPLocation = GetUniformLocation("gWVP");
    Texture0 = GetUniformLocation("tex");
    
    posAttrib = GetAttributeLocation("position");
    uvAttrib = GetAttributeLocation("texcoord");
    colorAttrib = GetAttributeLocation("color");
    
    return true;
}

GLint Shader::GetUniformLocation(const char* pUniformName)
{
    GLuint location = glGetUniformLocation(shaderProgram, pUniformName);
    
    /*if (location == INVALID_UNIFORM_LOCATION) {
        fprintf(stderr, "Warning! Unable to get the location of uniform '%s'\n", pUniformName);
    }*/
    
    return location;
}

GLint Shader::GetAttributeLocation(const char* pAttribName)
{
   GLuint location = glGetAttribLocation(shaderProgram, pAttribName);
    
    return location;
}

void Shader::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void Shader::Activate()
{
    SetWVP(Renderer::GetInstance()->GetWVP());
    
    glUniform1i(Texture0, 0);
    
    glUseProgram(shaderProgram);
    
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,  8*sizeof(float), 0);
    
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    
    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(uvAttrib);
    glEnableVertexAttribArray(colorAttrib);
    
}
