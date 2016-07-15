//
//  TestApp.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include <vector>

#include "TestApp.h"

void TestApp::PostInitialize()
{
    Renderer::GetInstance()->DRInitialize();
    
    camera = new Camera(Vector3(0.0f, 0.0f, -5.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    
    pos = Vector3(-50.0f, -50.0f, 00.0f);
    rot = Vector3(0.0f, 180.0f, 0.0f);
    scale = Vector3(0.09f, 0.09f, 0.09f);
    
    pos2 = Vector3(-40.0f, 10.0f, 50.0f);
    scale2 = Vector3(0.25f, 0.25f, 0.25f);
    
    model2 = new Model();
    //model2->LoadModel("./Resources/Models/ground.fbx");
    model2->LoadModel("./Resources/Models/hheli.obj");
    //model2->LoadModel("./Resources/Models/monkey.obj");
    //model2->LoadModel("./Resources/Models/spider.obj");
    //model2->LoadModel("./Resources/Models/sphere.obj");
    
    model = new Model();
    //model->LoadModel("./Resources/Models/jeep.obj");
    model->LoadModel("./Resources/Models/SoftSofa.obj");
    //model->LoadModel("./Resources/Models/spider.obj");
    //model->LoadModel("./Resources/Models/phoenix_ugv.md2");
    
    
    model3 = new Model();
    model3->LoadModel("./Resources/Models/quad.obj");
    pos3 = Vector3(0.0f, -50.0f, -50.0f);
    rot3 = Vector3(90.0f, 45.0f, 0.0f);
    scale3 = Vector3(100.0f, 100.0f, 100.0f);
    
    
    dirLight = new DirectionalLight();
    dirLight->Direction = Vector3(0.0f, -0.5f, 0.25f);
    dirLight->AmbientIntensity = 0.0f;
    dirLight->DiffuseIntensity = 2.0f;
    dirLight->Color = Vector3(1.0f, 1.0f, 1.0f);
    
    pLight1 = new PointLight();
    pLight1->Position = Vector3(-40.0f, 10.0f, -50.0f);
    pLight1->AmbientIntensity = 0.0f;
    pLight1->DiffuseIntensity = 4.5f;
    pLight1->Color = Vector3(1.0f, 0.0f, 0.0f);
    pLight1->Attenuation.Constant = 0.0f;
    pLight1->Attenuation.Exp = 0.005f;
    pLight1->Attenuation.Linear = 0.0f;
    
    pLight2 = new PointLight();
    pLight2->Position = Vector3(0.0f, 10.0f, -50.0f);
    pLight2->AmbientIntensity = 0.0f;
    pLight2->DiffuseIntensity = 4.5f;
    pLight2->Color = Vector3(0.0f, 1.0f, 0.0f);
    pLight2->Attenuation.Constant = 0.0f;
    pLight2->Attenuation.Exp = 0.005f;
    pLight2->Attenuation.Linear = 0.0f;
    
    pLight3 = new PointLight();
    pLight3->Position = Vector3(40.0f, 10.0f, -50.0f);
    pLight3->AmbientIntensity = 0.0f;
    pLight3->DiffuseIntensity = 4.5f;
    pLight3->Color = Vector3(0.0f, 0.0f, 1.0f);
    pLight3->Attenuation.Constant = 0.0f;
    pLight3->Attenuation.Exp = 0.005f;
    pLight3->Attenuation.Linear = 0.0f;
    
    Renderer::GetInstance()->SetDirectionLight(dirLight);
    Renderer::GetInstance()->AddPointLight(pLight1);
    Renderer::GetInstance()->AddPointLight(pLight2);
    Renderer::GetInstance()->AddPointLight(pLight3);
    
    mouseMove = false;
    cameraOffset = 200.0f;
    
    skybox = new Skybox();
    std::vector<const char*> skybox_files;
    skybox_files.push_back("./Resources/Textures/lake1_rt.jpg");
    skybox_files.push_back("./Resources/Textures/lake1_lf.jpg");
    skybox_files.push_back("./Resources/Textures/lake1_up.jpg");
    skybox_files.push_back("./Resources/Textures/lake1_dn.jpg");
    skybox_files.push_back("./Resources/Textures/lake1_bk.jpg");
    skybox_files.push_back("./Resources/Textures/lake1_ft.jpg");
    skybox->CreateSkybox("skybox", skybox_files);
}

void TestApp::Update()
{
    // Rotate + zoom camera
    if (Input::GetInstance()->IsMousePressed(0))
    {
        Vector2 curPos = Input::GetInstance()->GetMousePosition();
        if (mouseMove)
        {
            float deltaX = curPos.x - lastMousePos.x;
            float deltaY = curPos.y - lastMousePos.y;
            cameraRot.y += deltaX;
            cameraRot.x += deltaY;
        }
        mouseMove = true;
        lastMousePos = curPos;
    }
    else if (Input::GetInstance()->IsMousePressed(1))
    {
        Vector2 curPos = Input::GetInstance()->GetMousePosition();
        if (mouseMove)
        {
            float deltaY = curPos.y - lastMousePos.y;
            cameraOffset += deltaY;
        }
        mouseMove = true;
        lastMousePos = curPos;
    }
    else
    {
        mouseMove = false;
    }
    

    
    Matrix4f rTrans;
    Vector3 cameraPos = Vector3(0.0f, 0.0f, cameraOffset);
    Vector3 cameraForward = Vector3(0.0f, 0.0f, 1.0f);
    Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
    rTrans.CreateRotation(cameraRot);
    cameraPos = rTrans * cameraPos;
    cameraForward = rTrans * cameraForward;
    cameraUp = rTrans * cameraUp;
    camera->SetLocation(cameraPos);
    camera->SetForward(cameraForward);
    camera->SetUp(cameraUp);
    
    // Rendering
    
    Renderer::GetInstance()->SetCamera(camera);
    
    // Deferred shading pass
   /* Renderer::GetInstance()->DRBeginGeometryPass();
    model2->Render(pos2, rot, scale2);
    model->Render(pos, rot, scale);
    Renderer::GetInstance()->DRLightPass();*/
    
    Renderer::GetInstance()->BeginRender();
    
    //skybox->Render();
    
    model3->Render(pos3, rot3, scale3);
    model2->Render(pos2, rot, scale2);
    model->Render(pos, rot, scale);
    

    skybox->Render();
    
    Renderer::GetInstance()->EndRender();
}

