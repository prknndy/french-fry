//
//  MaterialManager.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/18/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__MaterialManager__
#define __GLFramework__MaterialManager__

#include <string>
#include <string.h>
#include <map>
#include <vector>

#include "Material.h"
#include "StandardShader.h"
#include "DRLightShader.h"
#include "UnlitShader.h"

class MaterialManager
{
    static MaterialManager* instance;
    std::map<std::string, Material> materials;
    std::vector<Shader> shaders;
    std::vector<Texture> textures;
    
    Material defaultMaterial;
    Material DRdefaultMaterial;
    StandardShader defaultShader;
    UnlitShader DRdefaultShader;
    Texture defaultTexture;
    
    DRLightShader DRlightShader;
    
    MaterialManager();
    ~MaterialManager();
    
public:
    static MaterialManager* GetInstance() {
        if (instance == NULL)
        {
            instance = new MaterialManager();
        }
        return instance;
    }
    
    void Initialize();
    void DRInitialize();
    
    Texture* GetTexture(std::string filename);
    Texture* CreateTexture(std::string filename);
    
    Material* GetMaterial(std::string matID);
    Material* GetDefaultMaterial();
    Material* CreateMaterial(std::string name, std::string filename);
    
    Shader* GetDRLightShader();
    Shader* GetDRDefaultShader() {
        return &DRdefaultShader;
    }
    
};

#endif /* defined(__GLFramework__MaterialManager__) */
