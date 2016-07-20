//
//  File.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/21/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "UnlitShader.h"
#include "Renderer.h"
#include "ShaderUniforms.h"



bool UnlitShader::Init()
{
    Shader::Init();
    
    posAttrib = GetAttributeLocation("position");
    uvAttrib = GetAttributeLocation("texcoord");
    colorAttrib = GetAttributeLocation("color");
    normalAttrib = GetAttributeLocation("normal");
    
    AddUniform(WVP_LOCATION);
    AddUniform(WORLD_LOCATION);
    
    Texture0 = GetUniformLocation("tex");
    
    return true;
}

void UnlitShader::Activate()
{
    Shader::Activate();
    
    SetUniformMat(WVP_LOCATION, Renderer::GetInstance()->GetWVP());
    SetUniformMat(WORLD_LOCATION, Renderer::GetInstance()->GetWorldTrans());
    
    //SetWVP(Renderer::GetInstance()->GetWVP());
    //SetWorld(Renderer::GetInstance()->GetWorldTrans());
    
}

void UnlitShader::UseMaterial(Material * mat)
{
    glUniform1i(Texture0, 0);
}
