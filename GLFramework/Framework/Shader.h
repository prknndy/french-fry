//
//  Shader.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Shader__
#define __GLFramework__Shader__

#include <map>

#include <GL/glew.h>
#include "Math3D.h"
#include "Lighting.h"

class Material;

class Shader
{
    // Progams
    //GLuint vertexShader;
    //GLuint fragmentShader;
    GLuint shaderProgram;
    
protected:
    // Attribs
    GLint posAttrib;
    GLint uvAttrib;
    GLint colorAttrib;
    GLint normalAttrib;
    
    std::map<const char*, GLint> uniforms;
    
    GLint GetUniformLocation(const char* pUniformName);
    GLint GetAttributeLocation(const char* pAttribName);
    
    void AddUniform(const char* uniformName);
    void AddPointLightUniform(const char* uniformName, int index);
    void AddDirectionalLightUniform(const char* uniformName, int index);
    
public:
    bool CreateShader(const char* vertFilename, const char* fragFilename);
    GLuint AddProgram(GLenum shaderType, const char* filename);
    bool CompileShader();
    //bool CompileShader(const char* vertFilename, const char* fragFilename);
    void Validate();
    virtual bool Init();
    virtual void Activate();
    virtual void UseMaterial(Material * mat) {}
    
    void SetUniform1f(const char* uniformName, float value);
    void SetUniform3f(const char* uniformName, Vector3 value);
    void SetUniformMat(const char* uniformName, const Matrix4f& value);
    
    bool HasUniform(const char* uniformName);
};

#endif /* defined(__GLFramework__Shader__) */
