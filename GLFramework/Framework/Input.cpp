//
//  Input.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//



#include "Input.h"

Input* Input::instance = NULL;

void Input::Initialize(GLFWwindow* _window)
{
    this->window = _window;
}

bool Input::IsKeyPressed(int key)
{
    //glfwSetKeyCallback(window, key_callback);
    //void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    int state = glfwGetKey(window, key);
    if (state == GLFW_PRESS)
    {
        return true;
    }
    
    return false;
}

bool Input::IsMousePressed(int button)
{
    //glfwSetMouseButtonCallback(window, mouse_button_callback);
    //void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)

    int state = glfwGetMouseButton(window, button);
    if (state == GLFW_PRESS)
    {
        return true;
    }
    
    return false;
}

Vector2 Input::GetMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    Vector2 ret((float)xpos, (float)ypos);
    return ret;
}
