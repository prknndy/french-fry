//
//  Mesh.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "Mesh.h"

void Mesh::Create()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    float vertices[] = {
        0.0f,  0.5f, 5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };
    
    
    glGenBuffers(1, &vbo); // Generate 1 buffer
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

Material* Mesh::GetMaterial()
{
    return this->mat;
}

void Mesh::SetMaterial(Material* _material)
{
    this->mat = _material;
}

void Mesh::Render()
{
    mat->Bind();
    
    glBindVertexArray(vao);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(0);
}