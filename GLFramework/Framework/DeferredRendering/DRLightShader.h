//
//  DRLightShader.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__DRLightShader__
#define __GLFramework__DRLightShader__

#include "StandardShader.h"
#include "Lighting.h"


class DRLightShader : public StandardShader
{
private:
    GLuint posTextureUnitLocation;
    GLuint normalTextureUnitLocation;
    GLuint colorTextureUnitLocation;
    GLuint screenSizeLocation;
    
public:
    virtual bool Init();
    virtual void Activate();
    virtual void UseMaterial(Material * mat);
    
    void SetPositionTextureUnit(unsigned int textureUnit);
    void SetColorTextureUnit(unsigned int textureUnit);
    void SetNormalTextureUnit(unsigned int textureUnit);
    void SetScreenSize(float width, float height);
    
};

#endif /* defined(__GLFramework__DRLightShader__) */
