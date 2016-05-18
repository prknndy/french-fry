//
//  Mesh.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Mesh__
#define __GLFramework__Mesh__

#include "Material.h"

class Mesh
{
    Material* mat;
    GLuint vbo;
    GLuint vao;

public:
    void Create();
    Material* GetMaterial();
    void SetMaterial(Material* _material);
    void Render();
};

#endif /* defined(__GLFramework__Mesh__) */
