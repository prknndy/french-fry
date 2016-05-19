//
//  Texture.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/16/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Texture__
#define __GLFramework__Texture__

#include <GL/glew.h>

class Texture
{
    GLuint texID;

public:
    void Create(const char* filename);
    void Bind(GLenum textureUnit);
};

#endif /* defined(__GLFramework__Texture__) */
