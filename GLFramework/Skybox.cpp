//
//  Skybox.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 6/11/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "MaterialManager.h"
#include "Renderer.h"

#include "Skybox.h"

void Skybox::CreateSkybox(std::string name, std::vector<const char*> filenames)
{
    /*glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    //box.CreateCube();
    Material* mat = MaterialManager::GetInstance()->CreateSkyboxMaterial(name, filenames);
    //box.SetMaterial(mat);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(6*sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11*sizeof(float), (void*)(8*sizeof(float)));
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);*/
    
    LoadModel("./Resources/Models/box.obj");
    //glBindVertexArray(vao);
    mat = MaterialManager::GetInstance()->CreateSkyboxMaterial(name, filenames);
    //glBindVertexArray(0);
}

void Skybox::Render()
{
    //glBindVertexArray(vao);
    //Renderer::GetInstance()->SetWorldTrans(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(20.0f, 20.0f, 20.0f));
    for (int i = 0; i < meshes.size(); i++)
    {
        //Renderer::GetInstance()->RenderSkybox(&meshes[i], MaterialManager::GetInstance()->GetDefaultMaterial());
        Renderer::GetInstance()->RenderSkybox(&meshes[i], mat);
    }
   // glBindVertexArray(0);
}
