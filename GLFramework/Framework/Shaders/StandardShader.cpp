//
//  StandardShader.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "StandardShader.h"
#include "Renderer.h"

bool StandardShader::Init()
{
    Shader::Init();
    
    posAttrib = GetAttributeLocation("position");
    uvAttrib = GetAttributeLocation("texcoord");
    colorAttrib = GetAttributeLocation("color");
    normalAttrib = GetAttributeLocation("normal");
    
    WVPLocation = GetUniformLocation("gWVP");
    WorldLocation = GetUniformLocation("gWorld");
    Texture0 = GetUniformLocation("tex");
    
    // lighting
    eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
    matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    matSpecularPowerLocation = GetUniformLocation("gMatSpecularPower");
    
    // Dir lighting
    
    dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
    dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
    dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    
    return true;
}

void StandardShader::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void StandardShader::SetWorld(const Matrix4f& world)
{
    glUniformMatrix4fv(WorldLocation, 1, GL_TRUE, (const GLfloat*)world.m);
}

void StandardShader::SetEyeWorldPos(const Vector3 eyeWorldPos)
{
    glUniform3f(eyeWorldPosLocation, eyeWorldPos.x, eyeWorldPos.y, eyeWorldPos.z);
}

void StandardShader::SetMatSpecularIntensity(float matIntensity)
{
    glUniform1f(matSpecularIntensityLocation, matIntensity);
}

void StandardShader::SetMatSpecularPower(float matPower)
{
    glUniform1f(matSpecularPowerLocation, matPower);
}

void StandardShader::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    Vector3 Direction = Light.Direction;
    Direction.Normalize();
    glUniform3f(dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}

void StandardShader::Activate()
{
    SetWVP(Renderer::GetInstance()->GetWVP());
    SetWorld(Renderer::GetInstance()->GetWorldTrans());
    
    glUniform1i(Texture0, 0);
    
    Shader::Activate();
    
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,  11*sizeof(float), 0);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(9*sizeof(float)));
    
    glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(uvAttrib);
    glEnableVertexAttribArray(colorAttrib);
    glEnableVertexAttribArray(normalAttrib);
    
}