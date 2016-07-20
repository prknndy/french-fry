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


void Shader::Validate()
{
    GLint status;
    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(shaderProgram, sizeof(buffer), NULL, buffer);
        fprintf(stderr, "Invalid shader program: '%s'\n", buffer);
        //return false;
    }
}

GLuint Shader::AddProgram(GLenum shaderType, const char* filename)
{
    GLint status;
    
    string buffer;
    if (!ReadFile(filename, buffer))
    {
        fputs ("Failed to read shader\n",stderr);
    }
    
    GLuint shader = glCreateShader(shaderType);
    
    const GLchar* p[1];
    p[0] = buffer.c_str();
    
    glShaderSource(shader, 1, p, NULL);
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char compilelog[512];
        glGetShaderInfoLog(shader, 512, NULL, compilelog);
        fputs (compilelog,stderr);
        fputs ("Failed to compile shader\n", stderr);
        return INVALID_OGL_VALUE;
    }
    
    glAttachShader(shaderProgram, shader);
    
    return shader;
}

bool Shader::CompileShader()
{
    GLint status;
    
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    
    glLinkProgram(shaderProgram);
    
    // Final error check
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
        char buffer[512];
		glGetProgramInfoLog(shaderProgram, sizeof(buffer), NULL, buffer);
		fprintf(stderr, "Error linking shader program: '%s'\n", buffer);
        return false;
	}
    
    return true;
}

bool Shader::CreateShader(const char* vertFilename, const char* fragFilename)
{
    LogDebug("Creating Shader:");
    LogDebug(fragFilename);
    
    shaderProgram = glCreateProgram();
    
    GLuint vertexShader = AddProgram(GL_VERTEX_SHADER, vertFilename);
    
    if (vertexShader == INVALID_OGL_VALUE)
    {
        return false;
    }
    
    GLuint fragShader = AddProgram(GL_FRAGMENT_SHADER, fragFilename);
    
    if (fragShader == INVALID_OGL_VALUE)
    {
        glDeleteShader(vertexShader);
        return false;
    }
    
    if (!CompileShader())
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragShader);
        return false;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    
    return Init();
}

bool Shader::Init()
{
    /*posAttrib = GetAttributeLocation("position");
    uvAttrib = GetAttributeLocation("texcoord");
    colorAttrib = GetAttributeLocation("color");
    normalAttrib = GetAttributeLocation("normal");*/
    return true;
}

GLint Shader::GetUniformLocation(const char* pUniformName)
{
    GLuint location = glGetUniformLocation(shaderProgram, pUniformName);
    
    if (location == INVALID_UNIFORM_LOCATION) {
        LogError("Unable to get location of uniform", pUniformName);
    }
    
    return location;
}

GLint Shader::GetAttributeLocation(const char* pAttribName)
{
   GLuint location = glGetAttribLocation(shaderProgram, pAttribName);
    
    if (location == INVALID_UNIFORM_LOCATION) {
        LogError("Unable to get location of attrib", pAttribName);
    }
    
    return location;
}

void Shader::AddUniform(const char* uniformName)
{
    GLuint location = GetUniformLocation(uniformName);
    
    if (location != INVALID_UNIFORM_LOCATION)
    {
        uniforms[uniformName] = location;
    }
}

bool Shader::HasUniform(const char* uniformName)
{
    if (uniforms.find(uniformName) != uniforms.end())
    {
        return true;
    }
    return false;
}

void Shader::SetUniform1f(const char* uniformName, float value)
{
    glUniform1f(uniforms[uniformName], value);
}

void Shader::SetUniform3f(const char* uniformName, Vector3 value)
{
    glUniform3f(uniforms[uniformName], value.x, value.y, value.z);
}

void Shader::SetUniformMat(const char* uniformName, const Matrix4f& value)
{
    glUniformMatrix4fv(uniforms[uniformName], 1, GL_TRUE, (const GLfloat*)value.m);
}


void Shader::Activate()
{
    glUseProgram(shaderProgram);
}

/*bool Shader::CompileShader(const char* vertFilename, const char* fragFilename)
 {
 
 GLint status;
 
 // Load vertex shader
 string buffer;
 if (!ReadFile(vertFilename, buffer))
 {
 fputs ("Failed to read vertex shader\n",stderr);
 }
 
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
 
 // Final error check
 glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
 if (status != GL_TRUE) {
 char buffer[512];
 glGetProgramInfoLog(shaderProgram, sizeof(buffer), NULL, buffer);
 fprintf(stderr, "Error linking shader program: '%s'\n", buffer);
 return false;
 }
 
 glValidateProgram(shaderProgram);
 glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &status);
 if (status != GL_TRUE) {
 char buffer[512];
 glGetProgramInfoLog(shaderProgram, sizeof(buffer), NULL, buffer);
 fprintf(stderr, "Invalid shader program: '%s'\n", buffer);
 //return false;
 }
 
 return true;
 }*/

