//
//  App.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__App__
#define __GLFramework__App__

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <thread>

#include "framework_includes.h"

class App
{
    GLFWwindow* window;
    float screenWidth;
    float screenHeight;
    bool isActive;
    
protected:
    virtual void PostInitialize() {};
    virtual void Update() {};
public:
    void Initialize(float _width, float _height);
    void Quit();
    void RenderUpdate();
    bool IsActive();
    
};

#endif /* defined(__GLFramework__App__) */
