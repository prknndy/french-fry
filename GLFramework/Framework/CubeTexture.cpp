//
//  CubeTexture.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 6/10/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "SOIL.h"

#include "Util.h"
#include "CubeTexture.h"

bool CubeTexture::Create(const char* _name, vector<const char*> filenames)
{
    
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
    
    //!!! No alpha support
    int width, height;
    unsigned char* image;
    
    for (int i = 0; i < filenames.size(); i++)
    {
        image = SOIL_load_image(filenames[i], &width, &height, 0, SOIL_LOAD_RGB);
    
        if (image == NULL)
        {
            LogError("Could not load texture", filenames[i]);
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            return false;
        }
    
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        
        SOIL_free_image_data(image);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    name = _name;
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return true;
}

void CubeTexture::Bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit); //GL_TEXTURE0
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
}