//
//  Shader.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Shader__
#define __GLFramework__Shader__

#include <GL/glew.h>
#include "Math3D.h"

class Shader
{
    // Progams
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    
    // Attribs
    GLint posAttrib;
    GLint uvAttrib;
    GLint colorAttrib;
    GLint normalAttrib;
    
    // Uniforms
    GLuint WVPLocation;
    GLuint WorldLocation;
    GLuint Texture0;
    
    
protected:
    GLint GetUniformLocation(const char* pUniformName);
    GLint GetAttributeLocation(const char* pAttribName);
    
public:
    bool CreateShader(const char* vertFilename, const char* fragFilename);
    bool CompileShader(const char* vertFilename, const char* fragFilename);
    void SetWVP(const Matrix4f& WVP);
    void SetWorld(const Matrix4f &world);
    void Activate();
    
};

#endif /* defined(__GLFramework__Shader__) */
