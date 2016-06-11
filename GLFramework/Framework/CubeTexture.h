//
//  CubeTexture.h
//  GLFramework
//
//  Created by Peter Kennedy on 6/10/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__CubeTexture__
#define __GLFramework__CubeTexture__

#include <string>
#include <string.h>
#include <vector>

#include "Texture.h"

class CubeTexture : public Texture
{
public:
    virtual bool Create(const char* _name, std::vector<const char*> filenames);
    virtual void Bind(GLenum textureUnit);
};

#endif /* defined(__GLFramework__CubeTexture__) */
