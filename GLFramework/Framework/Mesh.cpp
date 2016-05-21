//
//  Mesh.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "Mesh.h"
#include "Util.h"

Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{
    // TODO: fix
    /*if (vbo != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &vbo);
    }
    
    if (ibo != INVALID_OGL_VALUE)
    {
        glDeleteBuffers(1, &ibo);
    }*/
}

void Mesh::Create()
{
    
    float vertices[] = {
        0.0f,  0.5f, 5.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 5.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
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

void Mesh::CreateQuad()
{

    float vertices[] = {
        -1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    };
    
    
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    numIndices = 6;
    
    GLuint indices[] = {
        0, 1, 2, 2, 3, 0
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

int Mesh::GetMaterialIndex()
{
    return matIndex;
}

void Mesh::SetMaterialIndex(int _matIndex)
{
    this->matIndex = _matIndex;
}

void Mesh::Render()
{
    Render(mat);
}


void Mesh::Render(Material* _mat)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    //glBindVertexArray(vao);
    
    _mat->Bind();
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    
    //glBindVertexArray(0);
}

void Mesh::DirectRender()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(9*sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    //glBindVertexArray(vao);
    
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    
    //glBindVertexArray(0);
}