//
//  StandardShader.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include <string>

#include "StandardShader.h"
#include "ShaderUniforms.h"
#include "Renderer.h"

bool StandardShader::Init()
{
    Shader::Init();
    
    posAttrib = GetAttributeLocation("position");
    uvAttrib = GetAttributeLocation("texcoord");
    colorAttrib = GetAttributeLocation("color");
    normalAttrib = GetAttributeLocation("normal");
    
    AddUniform(WVP_LOCATION);
    AddUniform(WORLD_LOCATION);
    AddUniform(EYE_WORLD_POS_LOCATION);
    
    AddUniform(ROUGHNESS_LOCATION);
    AddUniform(LINEAR_ROUGHNESS_LOCATION);
    AddUniform(METAL_MASK_LOCATION);
    AddUniform(REFLECTIVITY_LOCATION);
    
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

// roughness = 1.0f - smoothness, linear smoothness = (1 - smoothness)^4
void StandardShader::SetSmoothness(float smoothness)
{
    float linearRoughness = 1.0f - smoothness;
    //float linearRoughness = roughness;//(1.0f - smoothness)*(1.0f - smoothness)*(1.0f - smoothness)*(1.0f - smoothness);
    float roughness = (0.5f + (linearRoughness / 2.0f)) * (0.5f + (linearRoughness / 2.0f));
    
    SetUniform1f(ROUGHNESS_LOCATION, roughness);
    SetUniform1f(LINEAR_ROUGHNESS_LOCATION, linearRoughness);
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

void StandardShader::SetPointLight(int index, const PointLight& Light)
{
    glUniform3f(pointLightLocation[index].Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(pointLightLocation[index].AmbientIntensity, Light.AmbientIntensity);
    glUniform1f(pointLightLocation[index].DiffuseIntensity, Light.DiffuseIntensity);
    
    glUniform3f(pointLightLocation[index].Position, Light.Position.x, Light.Position.y, Light.Position.z);
    glUniform1f(pointLightLocation[index].Constant, Light.Attenuation.Constant);
    glUniform1f(pointLightLocation[index].Linear, Light.Attenuation.Linear);
    glUniform1f(pointLightLocation[index].Exp, Light.Attenuation.Exp);
    
}

void StandardShader::SetPointLightCount(int count)
{
    glUniform1i(pointLightCount, count);
}

void StandardShader::Activate()
{
    Shader::Activate();
    
    //SetWVP(Renderer::GetInstance()->GetWVP());
    //SetWorld(Renderer::GetInstance()->GetWorldTrans());
     //SetEyeWorldPos(Renderer::GetInstance()->GetEyePos());
    
    SetUniformMat(WVP_LOCATION, Renderer::GetInstance()->GetWVP());
    SetUniformMat(WORLD_LOCATION, Renderer::GetInstance()->GetWorldTrans());
    SetUniform3f(EYE_WORLD_POS_LOCATION, Renderer::GetInstance()->GetEyePos());
    
    SetDirectionalLight(Renderer::GetInstance()->GetDirLight());
    int pLCount = Renderer::GetInstance()->GetPointLightCount();
    SetPointLightCount(pLCount);
    for (int i = 0; i < pLCount; i++)
    {
        SetPointLight(i, Renderer::GetInstance()->GetPointLight(i));
    }
   
    
}

void StandardShader::UseMaterial(Material * mat)
{
    MaterialParameters* params = mat->GetParameters();
    
    SetSmoothness(params->smoothness);
    
    SetUniform1f(REFLECTIVITY_LOCATION, params->reflectivity);
    SetUniform1f(METAL_MASK_LOCATION, params->metal);
    
    glUniform1i(Texture0, 0);
}