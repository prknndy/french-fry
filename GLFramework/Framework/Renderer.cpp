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
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Renderer::SetCamera(Camera* camera)
{
    this->currentCamera = camera;
}

void Renderer::BeginRender()
{
    Matrix4f cameraPosTrans, cameraRotTrans, proj;
    
    cameraPosTrans.CreateTranslate(currentCamera->GetLocation());
    cameraRotTrans.CreateWVP(currentCamera->GetForward(), currentCamera->GetUp());
    proj.CreateProj(screenWidth, screenHeight, 60.0f, 0.5f, 1000.0f);
    
    wvp = proj * cameraRotTrans * cameraPosTrans;
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::EndRender()
{
}

void Renderer::RenderMesh(Mesh* mesh)
{
    Shader* curShader = mesh->GetMaterial()->GetShader();
    curShader->SetWVP(wvp);
    curShader->Activate();
    mesh->GetMaterial()->Bind();
    mesh->Render();
}

Matrix4f& Renderer::GetWVP()
{
    return wvp;
}
