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
    defaultShader.CreateShader("./Resources/Shaders/SimpleVert.glsl", "./Resources/Shaders/SimpleFrag.glsl");
    
    defaultTexture.Create("./Resources/Textures/sample.png");
    
    defaultMaterial.Create(&defaultShader, &defaultTexture);
}

MaterialManager::MaterialManager()
{
    
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
    
    unsigned long texSize = textures.size() + 1;
    textures.resize(texSize);
    textures[texSize].Create(filename.c_str());
    
    Material* mat = new Material();
    mat->Create(&defaultShader, &textures[texSize]);
    
    return mat;
}


