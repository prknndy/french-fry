//
//  Renderer.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/13/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "Renderer.h"

Renderer* Renderer::instance = NULL;

Renderer::Renderer()
{
    
}

void Renderer::Initialize(int _screenWidth, int _screenHeight)
{
    screenWidth = _screenWidth;
    screenHeight = _screenHeight;
    
    projTrans.CreateProj(screenWidth, screenHeight, 60.0f, 0.5f, 10000.0f);
    
    gBuffer.Initialize(screenWidth, screenHeight);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Renderer::SetCamera(Camera* camera)
{
    this->currentCamera = camera;
    
    Matrix4f cameraPosTrans, cameraRotTrans;
    
    cameraPosTrans.CreateTranslate(currentCamera->GetLocation());
    cameraRotTrans.CreateWVP(currentCamera->GetForward(), currentCamera->GetUp());
    
    viewTrans = cameraRotTrans * cameraPosTrans;
}

void Renderer::BeginRender()
{
    //Matrix4f cameraPosTrans, cameraRotTrans, proj;
    
    //cameraPosTrans.CreateTranslate(currentCamera->GetLocation());
    //cameraRotTrans.CreateWVP(currentCamera->GetForward(), currentCamera->GetUp());
    //proj.CreateProj(screenWidth, screenHeight, 60.0f, 0.5f, 10000.0f);
    
    //wvp = proj *  cameraRotTrans * cameraPosTrans;
    
    vpTrans = projTrans * viewTrans;
    worldTrans.CreateIdentity();
    
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_DEPTH_TEST);
    
    //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndRender()
{
}

void Renderer::BeginGeometryPass()
{
    gBuffer.BindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::BeginLightpass()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    gBuffer.BindForReading();
    
    GLint halfWidth = (GLint) (screenWidth / 2.0f);
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
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);

    
}


void Renderer::RenderMesh(Mesh* mesh)
{

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
