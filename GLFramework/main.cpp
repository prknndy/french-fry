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

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    Renderer::GetInstance()->Initialize(800, 600);
    
    Camera* cam = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
    
    Renderer::GetInstance()->SetCamera(cam);
    
    Shader* s = new Shader();
    s->CreateShader("./Resources/Shaders/SimpleVert.glsl", "./Resources/Shaders/SimpleFrag.glsl");
    
    Texture* t = new Texture();
    t->Create("./Resources/Textures/sample.png");
    
    Material* mat = new Material;
    mat->Create(s, t);
    
    Mesh* mesh = new Mesh();
    mesh->Create();
    mesh->SetMaterial(mat);
    
    while(!glfwWindowShouldClose(window))
    {
        Renderer::GetInstance()->BeginRender();
        //Renderer::GetInstance()->RenderMesh(mesh);
        mesh->Render();
        Renderer::GetInstance()->EndRender();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

