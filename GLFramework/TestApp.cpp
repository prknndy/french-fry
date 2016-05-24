//
//  TestApp.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "TestApp.h"

void TestApp::PostInitialize()
{
    Renderer::GetInstance()->DRInitialize();
    
    camera = new Camera(Vector3(0.0f, 0.0f, -5.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    
    pos = Vector3(0.0f, -50.0f, 200.0f);
    rot = Vector3(0.0f, 0.0f, 0.0f);
    scale = Vector3(0.25f, 0.25f, 0.25f);
    
    pos2 = Vector3(0.0f, 0.0f, 150.0f);
    scale2 = Vector3(0.5f, 0.5f, 0.5f);
    
    model2 = new Model();
    model2->LoadModel("./Resources/Models/hheli.obj");
    //model2->LoadModel("./Resources/Models/monkey.obj");
    //model2->LoadModel("./Resources/Models/spider.obj");
    
    model = new Model();
    model->LoadModel("./Resources/Models/jeep.obj");
    //model->LoadModel("./Resources/Models/spider.obj");
    //model->LoadModel("./Resources/Models/phoenix_ugv.md2");
    
    dirLight = new DirectionalLight();
    dirLight->Direction = Vector3(0.0f, -0.5f, 1.0f);
    dirLight->AmbientIntensity = 0.2f;
    dirLight->DiffuseIntensity = 0.5f;
    dirLight->Color = Vector3(0.5f, 0.5f, 0.5f);
    
    pLight1 = new PointLight();
    pLight1->Position = Vector3(-200.0f, 300.0f, 200.0f);
    pLight1->AmbientIntensity = 0.0f;
    pLight1->DiffuseIntensity = 0.5f;
    pLight1->Color = Vector3(1.0f, 0.0f, 0.0f);
    pLight1->Attenuation.Constant = 0.0f;
    pLight1->Attenuation.Exp = 0.0f;
    pLight1->Attenuation.Linear = 0.1f;
    
    pLight2 = new PointLight();
    pLight2->Position = Vector3(0.0f, 300.0f, 200.0f);
    pLight2->AmbientIntensity = 0.0f;
    pLight2->DiffuseIntensity = 0.5f;
    pLight2->Color = Vector3(0.0f, 1.0f, 0.0f);
    pLight2->Attenuation.Constant = 0.0f;
    pLight2->Attenuation.Exp = 0.0f;
    pLight2->Attenuation.Linear = 0.1f;
    
    pLight3 = new PointLight();
    pLight3->Position = Vector3(200.0f, 300.0f, 200.0f);
    pLight3->AmbientIntensity = 0.0f;
    pLight3->DiffuseIntensity = 0.5f;
    pLight3->Color = Vector3(0.0f, 0.0f, 1.0f);
    pLight3->Attenuation.Constant = 0.0f;
    pLight3->Attenuation.Exp = 0.0f;
    pLight3->Attenuation.Linear = 0.1f;
    
    Renderer::GetInstance()->SetDirectionLight(dirLight);
    Renderer::GetInstance()->AddPointLight(pLight1);
    Renderer::GetInstance()->AddPointLight(pLight2);
    Renderer::GetInstance()->AddPointLight(pLight3);
    
}

void TestApp::Update()
{
    Renderer::GetInstance()->SetCamera(camera);
    
    // Deferred shading pass
    Renderer::GetInstance()->DRBeginGeometryPass();
    model->Render(pos, rot, scale);
    model2->Render(pos2, rot, scale2);
    model->Render(pos, rot, scale);
    Renderer::GetInstance()->DRLightPass();
    
    /*Renderer::GetInstance()->BeginRender();
    model->Render(pos, rot, scale);
    model2->Render(pos2, rot, scale2);
    Renderer::GetInstance()->EndRender();*/
}

