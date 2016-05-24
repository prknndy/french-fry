//
//  App.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "App.h"

void App::Initialize(float _width, float _height)
{
    screenWidth = _width;
    screenHeight = _height;
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    window = glfwCreateWindow(screenWidth, screenHeight, "French Fry", nullptr, nullptr); // Windowed
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    
    glewInit();
    
    Input::GetInstance()->Initialize(window);
    
    Renderer::GetInstance()->Initialize(screenWidth, screenHeight);
    MaterialManager::GetInstance()->Initialize();
    
    isActive = true;
    
    PostInitialize();
}

void App::RenderUpdate()
{
    if (!glfwWindowShouldClose(window))
    {
        Time::GetInstance()->Update();
        
        Update();
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    else
    {
        Quit();
    }
}

bool App::IsActive()
{
    return isActive;
}

void App::Quit()
{
    glfwTerminate();
    isActive = false;
}
