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
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);
    
    float vertices[] = {
        0.0f,  0.5f, 5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };
    
    
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    numIndices = 3;
    
    GLuint indices[] = {
        0, 1, 2
    };
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    numIndices = indices.size();
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
    
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
    //mat->Bind();
    
    /*glBindVertexArray(vao);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(0);*/
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}