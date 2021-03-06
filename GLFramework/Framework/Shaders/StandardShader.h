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
public:
    static const unsigned int MAX_POINT_LIGHTS = 4;
    
protected:
    // Uniforms
    GLuint Texture0;
    
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
    } pointLightLocation[MAX_POINT_LIGHTS];
    GLuint pointLightCount;
    
public:
    
    virtual bool Init();

    void SetDirectionalLight(const DirectionalLight& Light);
    void SetPointLight(int index, const PointLight& Light);
    void SetPointLightCount(int count);
    
    void SetSmoothness(float smoothness);

    virtual void UseMaterial(Material * mat);
    
    virtual void Activate();
};

#endif /* defined(__GLFramework__StandardShader__) */
