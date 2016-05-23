//
//  Time.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include <GLFW/glfw3.h>

#include "Time.h"

Time* Time::instance = NULL;

Time::Time()
{
    lastFrameTime = glfwGetTime();
    deltaTime = 0;
}

void Time::Update()
{
    double time = glfwGetTime();
    deltaTime = time - lastFrameTime;
    lastFrameTime = time;
}

double Time::DeltaTime()
{
    return deltaTime;
}
