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

class MaterialManager
{
    static MaterialManager* instance;
    std::map<std::string, Material> materials;
    std::vector<Shader> shaders;
    std::vector<Texture> textures;
    
    Material defaultMaterial;
    Shader defaultShader;
    Texture defaultTexture;
    
    MaterialManager();
    
public:
    static MaterialManager* GetInstance() {
        if (instance == NULL)
        {
            instance = new MaterialManager();
        }
        return instance;
    }
    
    void Initialize();
    Material* GetMaterial(std::string matID);
    Material* GetDefaultMaterial();
    Material* CreateMaterial(std::string name, std::string filename);
    
};

#endif /* defined(__GLFramework__MaterialManager__) */
