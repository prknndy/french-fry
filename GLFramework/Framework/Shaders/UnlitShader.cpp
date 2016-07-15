//
//  File.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/21/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "UnlitShader.h"
#include "Renderer.h"

bool UnlitShader::Init()
{
    Shader::Init();
    
    //posAttrib = GetAttributeLocation("position");
    //uvAttrib = GetAttributeLocation("texcoord");
    //colorAttrib = GetAttributeLocation("color");
    //normalAttrib = GetAttributeLocation("normal");
    
    WVPLocation = GetUniformLocation("gWVP");
    //WorldLocation = GetUniformLocation("gWorld");
    Texture0 = GetUniformLocation("tex");
    
    return true;
}

void UnlitShader::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void UnlitShader::SetWorld(const Matrix4f& world)
{
    glUniformMatrix4fv(WorldLocation, 1, GL_TRUE, (const GLfloat*)world.m);
}

void UnlitShader::Activate()
{
    Shader::Activate();
    
    SetWVP(Renderer::GetInstance()->GetWVP());
    //SetWorld(Renderer::GetInstance()->GetWorldTrans());
    
}

void UnlitShader::UseMaterial(Material * mat)
{
    glUniform1i(Texture0, 0);
}
