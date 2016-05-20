//
//  MaterialManager.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/18/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "MaterialManager.h"
#include "Util.h"

using namespace std;

MaterialManager* MaterialManager::instance = NULL;

void MaterialManager::Initialize()
{
    //defaultShader.CreateShader("./Resources/Shaders/SimpleVert.glsl", "./Resources/Shaders/SimpleFrag.glsl");
    
    defaultShader.CreateShader("./Resources/Shaders/DRSimpleVert.glsl", "./Resources/Shaders/DRSimpleFrag.glsl");
    
    defaultTexture.Create("./Resources/Textures/sample.png");
    
    defaultMaterial.Create(&defaultShader, &defaultTexture);
}

MaterialManager::MaterialManager()
{
    
}

Texture* MaterialManager::GetTexture(std::string filename)
{
    for (int i = 0; i < textures.size(); i++)
    {
        if (textures[i].GetName() == filename)
        {
            return &textures[i];
        }
    }
    
    return NULL;
}

Texture* MaterialManager::CreateTexture(std::string filename)
{
    /*unsigned long texSize = textures.size() + 1;
    textures.resize(texSize);
    if (!textures[texSize].Create(filename.c_str()))
    {
        return NULL;
    }
    return &textures[texSize];*/
    Texture* t = new Texture();
    if (!t->Create(filename.c_str()))
    {
        return NULL;
    }
    return t;
}

Material* MaterialManager::GetMaterial(std::string matID)
{
    auto it = materials.find(matID);
    if (it != materials.end())
    {
        return &materials[matID];
    }
    
    return NULL;
}

Material* MaterialManager::GetDefaultMaterial()
{
    return &defaultMaterial;
}

Material* MaterialManager::CreateMaterial(string name, string filename)
{
    
    LogDebug("Creating Material:");
    LogDebug(name.c_str());
    LogDebug(filename.c_str());
    
    Texture* tex = GetTexture(filename);
    if (tex == NULL)
    {
        tex = CreateTexture(filename);
        
        if (tex == NULL)
        {
            LogError("Failed Creating Material", name.c_str());
            return NULL;
        }
    }
    
    Material* mat = new Material();
    mat->Create(&defaultShader, tex);
    
    return mat;
}


