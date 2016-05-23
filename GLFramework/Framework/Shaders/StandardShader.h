//
//  StandardShader.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__StandardShader__
#define __GLFramework__StandardShader__

#include "Shader.h"
#include "Lighting.h"

class StandardShader : public Shader
{
    // Uniforms
    GLuint WVPLocation;
    GLuint WorldLocation;
    GLuint Texture0;
    
    GLuint eyeWorldPosLocation;
    GLuint matSpecularIntensityLocation;
    GLuint matSpecularPowerLocation;
    
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Direction;
    } dirLightLocation;
    
    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Constant;
        GLuint Linear;
        GLuint Exp;
    } pointLightLocation;
    
public:
    virtual bool Init();
    void SetWVP(const Matrix4f& WVP);
    void SetWorld(const Matrix4f &world);
    
    void SetEyeWorldPos(const Vector3 eyeWorldPos);
    void SetMatSpecularIntensity(float matIntensity);
    void SetMatSpecularPower(float matPower);
    void SetDirectionalLight(const DirectionalLight& Light);
    void SetPointLight(const PointLight& Light);
    
    virtual void Activate();
};

#endif /* defined(__GLFramework__StandardShader__) */
