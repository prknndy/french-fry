//
//  Texture.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/16/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "SOIL.h"

#include "Util.h"
#include "Texture.h"

Texture::Texture()
{
    
}

Texture::~Texture()
{
    
}

std::string Texture::GetName()
{
    return name;
}

bool Texture::Create(const char* filename)
{
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    
    //!!! No alpha support
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    
    if (image == NULL)
    {
        LogError("Could not load texture", filename);
        return false;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    name = filename;
    
    return true;
    
    //glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);
    //glUniform1i(gSampler, 0);
}

void Texture::Bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit); //GL_TEXTURE0
    glBindTexture(GL_TEXTURE_2D, texID);
}
