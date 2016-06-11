//
//  Mesh.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Mesh__
#define __GLFramework__Mesh__

#include <vector>

#include "Math3D.h"
#include "Material.h"

class Mesh
{
    Material* mat;
    int matIndex;
    GLuint vbo;
    GLuint vao;
    GLuint ibo;
    
    unsigned int numIndices;

public:
    Mesh();
    ~Mesh();
    void Create();
    void CreateQuad();
    void CreateCube();
    void Create(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    
    void Render(Material* mat);
    void Render();
    void DirectRender();
    
    Material* GetMaterial();
    void SetMaterial(Material* _material);
    int GetMaterialIndex();
    void SetMaterialIndex(int _matIndex);
};

#endif /* defined(__GLFramework__Mesh__) */
