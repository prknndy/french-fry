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
    // Uniforms
    GLuint WVPLocation;
    GLuint WorldLocation;
    GLuint Texture0;

public:
    virtual bool Init();
    void SetWVP(const Matrix4f& WVP);
    void SetWorld(const Matrix4f &world);
    
    virtual void Activate();
};

#endif /* defined(__GLFramework__File__) */
