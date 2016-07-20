//
//  File.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/21/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__File__
#define __GLFramework__File__

#include "Shader.h"


class UnlitShader : public Shader
{
    GLuint Texture0;

public:
    virtual bool Init();
    
    virtual void Activate();
    virtual void UseMaterial(Material * mat);
};

#endif /* defined(__GLFramework__File__) */
