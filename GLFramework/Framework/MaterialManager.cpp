//
//  MaterialManager.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/18/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "CubeTexture.h"
#include "MaterialManager.h"
#include "Util.h"

using namespace std;

MaterialManager* MaterialManager::instance = NULL;

MaterialManager::MaterialManager()
{
    
}

MaterialManager::~MaterialManager()
{
    
}


void MaterialManager::Initialize()
{
    //defaultShader.CreateShader("./Resources/Shaders/StandardVert.glsl", "./Resources/Shaders/StandardFrag.glsl");
    
    defaultShader.CreateShader("./Resources/Shaders/PBRVert.glsl", "./Resources/Shaders/PBRFrag.glsl");
    
    DRdefaultShader.CreateShader("./Resources/Shaders/DRSimpleVert.glsl", "./Resources/Shaders/DRSimpleFrag.glsl");
    
    skyboxShader.CreateShader("./Resources/Shaders/SkyboxVert.glsl", "./Resources/Shaders/SkyboxFrag.glsl");
    
    defaultTexture.Create("./Resources/Textures/white.png");
    
    MaterialParameters mp = MaterialParameters();
    mp.smoothness = 0.15f;
    mp.reflectivity = 0.2f;
    mp.metal = 0.0f;
    
    defaultMaterial.Create(&defaultShader, &defaultTexture);
    defaultMaterial.SetParameters(mp);
    
    DRdefaultMaterial.Create(&DRdefaultShader, &defaultTexture);
    DRdefaultMaterial.SetParameters(mp);
}

void MaterialManager::DRInitialize()
{
    DRlightShader.CreateShader("./Resources/Shaders/DRLightVert.glsl", "./Resources/Shaders/DRDirLightFrag.glsl");
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

CubeTexture* MaterialManager::CreateCubeTexture(std::string name, std::vector<const char*> filenames)
{
    CubeTexture* t = new CubeTexture();
    if (!t->Create(name.c_str(), filenames))
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
    
    if (name.compare("hheli.bmp") == 0)
    {
        Shader* s = new StandardShader();
        s->CreateShader("./Resources/Shaders/PBRVert.glsl", "./Resources/Shaders/PBRFrag.glsl");
        MaterialParameters mp = MaterialParameters();
        mp.smoothness = 0.9f;
        mp.reflectivity = 0.7f;
        mp.metal = 1.0f;
        mat->Create(s, tex);
        //mat->Create(&defaultShader, tex);
        mat->SetParameters(mp);
    }
    else
    {
        mat->Create(&defaultShader, tex);
    }
    
    return mat;
}

Material* MaterialManager::CreateSkyboxMaterial(std::string name, std::vector<const char*> filenames)
{
    LogDebug("Creating Skybox Material:");
    LogDebug(name.c_str());
    
    CubeTexture* tex = CreateCubeTexture(name, filenames);
    if (tex == NULL)
    {
        LogError("Failed Creating Material", name.c_str());
        return NULL;
    }
    
    Material* mat = new Material();
    mat->Create(&skyboxShader, tex);
    
    return mat;
}

Shader* MaterialManager::GetDRLightShader()
{
    return &DRlightShader;
}


