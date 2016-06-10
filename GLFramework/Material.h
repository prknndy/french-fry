//
//  Material.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Material__
#define __GLFramework__Material__

#include "Shader.h"
#include "Texture.h"


//diffuseColor = (1 − metalMask) baseColor
//f0 = 0.16 reflectance2 (1 − metalMask) + baseColor metalMask
struct MaterialParameters
{
    float smoothness;
    float reflectivity;
    float metal;
    
    MaterialParameters()
    {
        smoothness = 0.0f;
        reflectivity = 0.0f;
        metal = 0.0f;
    }
    
    MaterialParameters(float _smoothness, float _reflectivity, float _metal) : smoothness(_smoothness), reflectivity(_reflectivity), metal(_metal)
    {
        
    }
};

class Material
{
    Shader* shader;
    Texture* texture;
    MaterialParameters parameters;
public:
    void Create(Shader* _shader, Texture* texture);
    void SetParameters(MaterialParameters mp);
    void SetShader(Shader* _shader);
    
    MaterialParameters* GetParameters()
    {
        return &parameters;
    }
    
    Shader* GetShader();
    
    Texture* GetTexture()
    {
        return texture;
    }
    
    void Bind();
};

#endif /* defined(__GLFramework__Material__) */
