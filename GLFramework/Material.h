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

class Material
{
    Shader* shader;
    Texture* texture;
public:
    void Create(Shader* _shader, Texture* texture);
    void SetShader(Shader* _shader);
    Shader* GetShader();
    void Bind();
};

#endif /* defined(__GLFramework__Material__) */
