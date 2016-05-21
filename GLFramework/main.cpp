//
//  main.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 4/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <thread>

#include "framework_includes.h"

int main(int argc, const char * argv[])
{
    int screenWidth = 1024;
    int screenHeight = 512;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "French Fry", nullptr, nullptr); // Windowed
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;

    glewInit();
    
    Renderer::GetInstance()->Initialize(screenWidth, screenHeight);
    MaterialManager::GetInstance()->Initialize();
    //Renderer::GetInstance()->DRInitialize();
    
    Camera* cam = new Camera(Vector3(0.0f, 0.0f, -5.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    Camera* downCam = new Camera(Vector3(0.0f, 10.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f));
    
    Renderer::GetInstance()->SetCamera(cam);
    
    /*Mesh* mesh = new Mesh();
    mesh->Create();
    mesh->SetMaterial(mat);*/
    
    Model* model = new Model();
    model->LoadModel("./Resources/Models/jeep.obj");
    //model->LoadModel("./Resources/Models/spider.obj");
    //model->LoadModel("./Resources/Models/phoenix_ugv.md2");
    Vector3 pos(0.0f, -50.0f, 200.0f);
    Vector3 rot(0.0f, 0.0f, 0.0f);
    Vector3 scale(0.25f, 0.25f, 0.25f);
    Matrix4f trans;
    trans.CreateIdentity();
    
    while(!glfwWindowShouldClose(window))
    {
        // Deferred shading pass
        //Renderer::GetInstance()->DRBeginGeometryPass();
        //model->Render(pos, rot, scale);
        //Renderer::GetInstance()->DRLightPass();
        
        Renderer::GetInstance()->BeginRender();
        model->Render(pos, rot, scale);
        Renderer::GetInstance()->EndRender();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

