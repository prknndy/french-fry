//
//  Input.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Input__
#define __GLFramework__Input__

#include <GLFW/glfw3.h>

#include "Math3D.h"

class Input
{
    GLFWwindow* window;
    Input() { };
    static Input* instance;
public:
    static Input* GetInstance(){
        if (instance == NULL)
        {
            instance = new Input();
        }
        return instance;
    }
    void Initialize(GLFWwindow* window);
    bool IsKeyPressed(int key);
    bool IsMousePressed(int button);
    Vector2 GetMousePosition();
    
};

#endif /* defined(__GLFramework__Input__) */
