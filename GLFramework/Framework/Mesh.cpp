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


void Mesh::CreateQuad()
{
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);

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
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(8*sizeof(float)));
    
    glBindVertexArray(0);

}

void Mesh::CreateCube()
{
    float vertices[] = {
        // Front
        1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
        1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
         -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
         -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
        // Back
        -1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        // Left
        -1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
        // Right
        1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        // Top
        1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        -1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
        // Bottom
        1.0f,  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
        -1.0f,  -1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
    };
    
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    numIndices = 36;
    
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,
        
        8, 9, 10,
        10, 11, 8,
        
        12, 13, 14,
        14, 15, 12,
        
        16, 17, 18,
        18, 19, 16,
        
        20, 21, 22,
        22, 23, 20
        
    };
    
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(8*sizeof(float)));
    
    glBindVertexArray(0);
}

void Mesh::Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    
    glBindVertexArray(vao);
    
    numIndices = indices.size();
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, &indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(8*sizeof(float)));

    glBindVertexArray(0);
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
    //_mat->Bind();
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    _mat->Bind();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::DirectRender()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
