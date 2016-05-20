//
//  GBuffer.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/19/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__GBuffer__
#define __GLFramework__GBuffer__

#include <GL/glew.h>

/*
 #define GBUFFER_POSITION_TEXTURE_UNIT 0
 #define GBUFFER_DIFFUSE_TEXTURE_UNIT  1
 #define GBUFFER_NORMAL_TEXTURE_UNIT   2
 #define GBUFFER_TEXCOORD_TEXTURE_UNIT 3
 */

class GBuffer
{
public:
    enum GBUFFER_TEXTURE_TYPE {
        GBUFFER_TEXTURE_TYPE_POSITION,
        GBUFFER_TEXTURE_TYPE_DIFFUSE,
        GBUFFER_TEXTURE_TYPE_NORMAL,
        GBUFFER_TEXTURE_TYPE_TEXCOORD,
        GBUFFER_NUM_TEXTURES
    };
    
private:
    
    GLuint fbo;
    GLuint textures[GBUFFER_NUM_TEXTURES];
    GLuint depthTexture;
    
public:
    GBuffer();
    ~GBuffer();
    bool Initialize(int screenWidth, int screenHeight);
    void BindForWriting();
    void BindForReading();
    void SetReadBuffer(GBUFFER_TEXTURE_TYPE gBufferTextureType);
    
};

#endif /* defined(__GLFramework__GBuffer__) */
