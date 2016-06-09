//
//  Renderer.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/13/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "Renderer.h"
#include "MaterialManager.h"

Renderer* Renderer::instance = NULL;

Renderer::Renderer()
{
    isInDR = false;
}

void Renderer::Initialize(int _screenWidth, int _screenHeight)
{
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    
    projTrans.CreateProj(screenWidth, screenHeight, 60.0f, 0.5f, 10000.0f);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    
}

/*
 *  Forward
 */

void Renderer::BeginRender()
{
    vpTrans = projTrans * viewTrans;
    worldTrans.CreateIdentity();
    
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_DEPTH_TEST);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndRender()
{

}

/*
 *   End Forward
 */

/*
 *   DR
 */

void Renderer::DRInitialize()
{
    gBuffer.Initialize(2.0f * screenWidth, 2.0f * screenHeight);
    
    MaterialManager::GetInstance()->DRInitialize();
    DRLightShader* drLightShader = (DRLightShader*) MaterialManager::GetInstance()->GetDRLightShader();
    
    glBindVertexArray(vao);
    quad.CreateQuad();

    drLightShader->Activate();
    
    drLightShader->SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    drLightShader->SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    drLightShader->SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    drLightShader->SetScreenSize(screenWidth*2.0f, screenHeight*2.0f);

    glBindVertexArray(0);
}

void Renderer::DRBeginGeometryPass()
{
    isInDR = true;
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    vpTrans = projTrans * viewTrans;
    worldTrans.CreateIdentity();
    
    gBuffer.BindForWriting();
    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glDisable(GL_BLEND);
    
    MaterialManager::GetInstance()->GetDRDefaultShader()->Activate();
}

void Renderer::DRLightPass()
{
    DRBeginLightpass();
    //DRDirectionalLightPass();
    DRPointLightPass();
    DREndLightPass();
    isInDR = false;
}

void Renderer::DRBeginLightpass()
{
    glDepthMask(GL_FALSE);
    
    glDisable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND);
   	glBlendEquation(GL_FUNC_ADD);
   	glBlendFunc(GL_ONE, GL_ONE);
    
    gBuffer.BindForReading();
    glClear(GL_COLOR_BUFFER_BIT);
    
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    /*GLint halfWidth = (GLint) (screenWidth / 2.0f);
    GLint halfHeight = (GLint) (screenHeight / 2.0f);
    
    gBuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    glBlitFramebuffer(0, 0, screenWidth, screenHeight,
                      0, 0, halfWidth, halfHeight,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    gBuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    glBlitFramebuffer(0, 0, screenWidth, screenHeight,
                      0, halfHeight, halfWidth, screenHeight,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    gBuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glBlitFramebuffer(0, 0, screenWidth, screenHeight,
                      halfWidth, halfHeight, screenWidth, screenHeight,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    gBuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
    glBlitFramebuffer(0, 0, screenWidth, screenHeight,
                      halfWidth, 0, screenWidth, halfHeight,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);*/

    
}

void Renderer::DRDirectionalLightPass()
{
    glBindVertexArray(vao);
    Matrix4f tWVP;
    tWVP.CreateIdentity();

    Material* m = MaterialManager::GetInstance()->GetDefaultMaterial();
    m->GetShader()->Activate();
    //((StandardShader*) m->GetShader())->SetWVP(tWVP);

    DRLightShader* drLightShader = (DRLightShader*) MaterialManager::GetInstance()->GetDRLightShader();
    drLightShader->Activate();
    drLightShader->SetWVP(tWVP);
    drLightShader->SetEyeWorldPos(currentCamera->GetLocation());
    //drLightShader->SetDirectionalLight(&dirLight);
    //drLightShader->SetMatSpecularIntensity(0.5f);
    //drLightShader->SetMatSpecularPower(0.5f);
    
    quad.DirectRender();
    glBindVertexArray(0);
    
    // Old ref
    /*(drLightShader.Activate();
     
     MaterialManager::GetInstance()->DRlightShader.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
     MaterialManager::GetInstance()->DRlightShader.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);;
     MaterialManager::GetInstance()->DRlightShader.SetScreenSize(screenWidth, screenHeight);
     MaterialManager::GetInstance()->DRlightShader.SetWVP(tWVP);
     drLightShader.SetEyeWorldPos(currentCamera->GetLocation());
     drLightShader.SetDirectionalLight(dirLight);*/

}

void Renderer::DRPointLightPass()
{
    glBindVertexArray(vao);
    Matrix4f tWVP;
    tWVP.CreateIdentity();
    
    //Material* m = MaterialManager::GetInstance()->GetDefaultMaterial();
    
    //m->GetShader()->Activate();
    //StandardShader* drLightShader = (StandardShader*) m->GetShader();
    //m->Bind();
    
    DRLightShader* drLightShader = (DRLightShader*) MaterialManager::GetInstance()->GetDRLightShader();
    drLightShader->Activate();
    drLightShader->SetWVP(tWVP);
    drLightShader->SetEyeWorldPos(currentCamera->GetLocation());
    
    drLightShader->SetDirectionalLight(GetDirLight());
    
    drLightShader->SetPointLightCount(GetPointLightCount());
    for (int i = 0; i < GetPointLightCount(); i++)
    {
        drLightShader->SetPointLight(i, GetPointLight(i));
    }
    
    quad.DirectRender();
    glBindVertexArray(0);
}

void Renderer::DREndLightPass()
{
    /*gBuffer.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    glBlitFramebuffer(0, 0, screenWidth, screenHeight,
                      0, 0, screenWidth, screenHeight,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);*/
}

/*
 * End DR
 */

void Renderer::SetDirectionLight(DirectionalLight* _dirLight)
{
    dirLight = _dirLight;
}

void Renderer::AddPointLight(PointLight* pointLight)
{
    pointLights.push_back(pointLight);
}

void Renderer::RemovePointLight(PointLight *pointLight)
{
    int index = -1;
    for (int i = 0; i < pointLights.size(); i++)
    {
        if (pointLights[i] == pointLight)
        {
            index = i;
            break;
        }
    }
    
    if (index != -1)
    {
        pointLights.erase(pointLights.begin() + index);
    }
}

void Renderer::RenderModel(Model* model)
{

}


void Renderer::RenderMesh(Mesh* mesh)
{
    Material* m = mesh->GetMaterial();
    Shader* s;
    if (!isInDR)
    {
        s = m->GetShader();
    }
    else
    {
        s = MaterialManager::GetInstance()->GetDRDefaultShader();
    }
    s->UseMaterial(m);
    s->Activate();
    //m->Bind();
    
    mesh->Render();
}

void Renderer::SetCamera(Camera* camera)
{
    this->currentCamera = camera;
    
    Matrix4f cameraPosTrans, cameraRotTrans;
    
    cameraPosTrans.CreateTranslate(currentCamera->GetLocation());
    cameraRotTrans.CreateWVP(currentCamera->GetForward(), currentCamera->GetUp());
    
    viewTrans = cameraRotTrans * cameraPosTrans;
    
    eyePos = currentCamera->GetLocation();
}

void Renderer::SetWorldTrans(Matrix4f* _worldTrans)
{
    worldTrans = *_worldTrans;
}

void Renderer::SetWorldTrans(Vector3 pos, Vector3 rot, Vector3 scale)
{
    Matrix4f pTrans, rTrans, sTrans;
    pTrans.CreateTranslate(pos);
    rTrans.CreateRotation(rot);
    sTrans.CreateScale(scale);
    
    worldTrans = pTrans * rTrans * sTrans;
}

Matrix4f& Renderer::GetWVP()
{
    wvp = vpTrans * worldTrans;
    return wvp;
}

Matrix4f& Renderer::GetWorldTrans()
{
    return worldTrans;
}

Vector3& Renderer::GetEyePos()
{
    return eyePos;
}

DirectionalLight& Renderer::GetDirLight()
{
    return (*dirLight);
}

PointLight& Renderer::GetPointLight(int index)
{
    return *(pointLights[index]);
}

int Renderer::GetPointLightCount()
{
    return (int)pointLights.size();
}

