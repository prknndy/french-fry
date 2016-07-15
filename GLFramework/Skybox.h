//
//  Skybox.h
//  GLFramework
//
//  Created by Peter Kennedy on 6/11/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Skybox__
#define __GLFramework__Skybox__

#include "Material.h"
#include "Mesh.h"

class Skybox : public Model
{
    //GLuint vao;
    //Mesh box;
    Material* mat;
public:
    void CreateSkybox(std::string name, std::vector<const char*> filenames);
    void Render();
};

#endif /* defined(__GLFramework__Skybox__) */
