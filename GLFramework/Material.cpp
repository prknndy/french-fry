//
//  Material.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/14/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "Material.h"

void Material::Create(Shader* _shader, Texture* _texture)
{
    this->shader = _shader;
    this->texture = _texture;
}

void Material::SetShader(Shader* _shader)
{
    this->shader = _shader;
}

Shader* Material::GetShader()
{
    return this->shader;
}

void Material::Bind()
{
    //shader->Activate();
    texture->Bind(GL_TEXTURE0);
}