//
//  DRLightShader.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__DRLightShader__
#define __GLFramework__DRLightShader__

#include "Shader.h"
#include "Lighting.h"

class DRLightShader : public Shader
{
private:
    GLuint WVPLocation;
    GLuint WorldLocation;
    GLuint posTextureUnitLocation;
    GLuint normalTextureUnitLocation;
    GLuint colorTextureUnitLocation;
    
    GLuint eyeWorldPosLocation;
    GLuint matSpecularIntensityLocation;
    GLuint matSpecularPowerLocation;
    GLuint screenSizeLocation;
    
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Direction;
    } dirLightLocation;
    
public:
    virtual bool Init();
    virtual void Activate();
    
    void SetWVP(const Matrix4f& WVP);
    void SetWorld(const Matrix4f &world);
    void SetPositionTextureUnit(unsigned int textureUnit);
    void SetColorTextureUnit(unsigned int textureUnit);
    void SetNormalTextureUnit(unsigned int textureUnit);
    void SetEyeWorldPos(const Vector3 eyeWorldPos);
    void SetMatSpecularIntensity(float matIntensity);
    void SetMatSpecularPower(float matPower);
    void SetScreenSize(float width, float height);
    
    void SetDirectionalLight(const DirectionalLight& Light);
};

#endif /* defined(__GLFramework__DRLightShader__) */
