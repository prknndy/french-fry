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
    camera = new Camera(Vector3(0.0f, 0.0f, -5.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    
    pos = Vector3(0.0f, -50.0f, 200.0f);
    rot = Vector3(0.0f, 0.0f, 0.0f);
    scale = Vector3(0.25f, 0.25f, 0.25f);
    
    model = new Model();
    model->LoadModel("./Resources/Models/jeep.obj");
    //model->LoadModel("./Resources/Models/spider.obj");
    //model->LoadModel("./Resources/Models/phoenix_ugv.md2");
}

void TestApp::Update()
{
    // Deferred shading pass
    //Renderer::GetInstance()->DRBeginGeometryPass();
    //model->Render(pos, rot, scale);
    //Renderer::GetInstance()->DRLightPass();
    Renderer::GetInstance()->SetCamera(camera);
    Renderer::GetInstance()->BeginRender();
    model->Render(pos, rot, scale);
    Renderer::GetInstance()->EndRender();
}

