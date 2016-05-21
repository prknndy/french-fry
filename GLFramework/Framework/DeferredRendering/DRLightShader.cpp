//
//  DRLightShader.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "DRLightShader.h"
#include "Renderer.h"

bool DRLightShader::Init()
{
    Shader::Init();
    
    posAttrib = GetAttributeLocation("position");
    
    WVPLocation = GetUniformLocation("gWVP");
    //WorldLocation = GetUniformLocation("gWorld");
    posTextureUnitLocation = GetUniformLocation("gPositionMap");
    colorTextureUnitLocation = GetUniformLocation("gColorMap");
    normalTextureUnitLocation = GetUniformLocation("gNormalMap");
    screenSizeLocation = GetUniformLocation("gScreenSize");
    
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

void DRLightShader::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(WVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}

void DRLightShader::SetWorld(const Matrix4f& world)
{
    //glUniformMatrix4fv(WorldLocation, 1, GL_TRUE, (const GLfloat*)world.m);
}

void DRLightShader::SetPositionTextureUnit(unsigned int textureUnit)
{
    glUniform1i(posTextureUnitLocation, textureUnit);
}

void DRLightShader::SetColorTextureUnit(unsigned int textureUnit)
{
    glUniform1i(colorTextureUnitLocation, textureUnit);
}

void DRLightShader::SetNormalTextureUnit(unsigned int textureUnit)
{
    glUniform1i(normalTextureUnitLocation, textureUnit);
}

void DRLightShader::SetEyeWorldPos(const Vector3 eyeWorldPos)
{
    glUniform3f(eyeWorldPosLocation, eyeWorldPos.x, eyeWorldPos.y, eyeWorldPos.z);
}

void DRLightShader::SetMatSpecularIntensity(float matIntensity)
{
    glUniform1f(matSpecularIntensityLocation, matIntensity);
}

void DRLightShader::SetMatSpecularPower(float matPower)
{
    glUniform1f(matSpecularPowerLocation, matPower);
}

void DRLightShader::SetScreenSize(float width, float height)
{
    glUniform2f(screenSizeLocation, width, height);
}

void DRLightShader::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(dirLightLocation.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(dirLightLocation.AmbientIntensity, Light.AmbientIntensity);
    Vector3 Direction = Light.Direction;
    Direction.Normalize();
    glUniform3f(dirLightLocation.Direction, Direction.x, Direction.y, Direction.z);
    glUniform1f(dirLightLocation.DiffuseIntensity, Light.DiffuseIntensity);
}

void DRLightShader::Activate()
{
    SetWVP(Renderer::GetInstance()->GetWVP());
    //SetWorld(Renderer::GetInstance()->GetWorldTrans());
    
    glUniform1i(posTextureUnitLocation, 0);
    
    Shader::Activate();
    
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,  11*sizeof(float), 0);
    
    glEnableVertexAttribArray(posAttrib);
}