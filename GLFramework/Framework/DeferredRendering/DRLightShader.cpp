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
    uvAttrib = GetAttributeLocation("texcoord");
    colorAttrib = GetAttributeLocation("color");
    normalAttrib = GetAttributeLocation("normal");

    colorTextureUnitLocation = GetUniformLocation("gColorMap");
    posTextureUnitLocation = GetUniformLocation("gPositionMap");
    normalTextureUnitLocation = GetUniformLocation("gNormalMap");
    screenSizeLocation = GetUniformLocation("gScreenSize");
    
    WVPLocation = GetUniformLocation("gWVP");
    
    // Lighting
    eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
    matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
    matSpecularPowerLocation = GetUniformLocation("gMatSpecularPower");
    
    // Dir lighting
    dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
    dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
    dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
    dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    
    // Point lighting
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        char buffer[128];
        memset(buffer, 0, sizeof(buffer));
        
        sprintf(buffer, "gPointLight[%d].Base.Color", i);
        pointLightLocation[i].Color = GetUniformLocation(buffer);
        
        sprintf(buffer, "gPointLight[%d].Base.AmbientIntensity", i);
        pointLightLocation[i].AmbientIntensity = GetUniformLocation(buffer);
        
        sprintf(buffer, "gPointLight[%d].Base.DiffuseIntensity", i);
        pointLightLocation[i].DiffuseIntensity = GetUniformLocation(buffer);
        
        sprintf(buffer, "gPointLight[%d].Position", i);
        pointLightLocation[i].Position = GetUniformLocation(buffer);
        
        sprintf(buffer, "gPointLight[%d].Atten.Constant", i);
        pointLightLocation[i].Constant = GetUniformLocation(buffer);
        
        sprintf(buffer, "gPointLight[%d].Atten.Linear", i);
        pointLightLocation[i].Linear = GetUniformLocation(buffer);
        
        sprintf(buffer, "gPointLight[%d].Atten.Exp", i);
        pointLightLocation[i].Exp = GetUniformLocation(buffer);
    }
    pointLightCount = GetUniformLocation("gNumPointLights");
    
    return true;
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

void DRLightShader::SetScreenSize(float width, float height)
{
    glUniform2f(screenSizeLocation, width, height);
}

void DRLightShader::Activate()
{
    //SetWVP(Renderer::GetInstance()->GetWVP());
    /*SetDirectionalLight(Renderer::GetInstance()->GetDirLight());
    int pLCount = Renderer::GetInstance()->GetPointLightCount();
    SetPointLightCount(pLCount);
    for (int i = 0; i < pLCount; i++)
    {
        SetPointLight(i, Renderer::GetInstance()->GetPointLight(i));
    }
    SetEyeWorldPos(Renderer::GetInstance()->GetEyePos());*/
    
    SetMatSpecularIntensity(0.5f);
    SetMatSpecularPower(0.5f);
    
    Shader::Activate();
}

void DRLightShader::UseMaterial(Material * mat)
{
    // FIX
    SetMatSpecularIntensity(0.5f);
    SetMatSpecularPower(0.5f);
}