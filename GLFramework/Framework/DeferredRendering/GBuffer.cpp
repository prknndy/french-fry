//
//  GBuffer.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/19/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "GBuffer.h"
#include "Util.h"

GBuffer::GBuffer()
{
    fbo = 0;
    ZERO_MEM(textures);
    depthTexture = 0;
}

GBuffer::~GBuffer()
{
   if (fbo != 0)
   {
       glDeleteFramebuffers(1, &fbo);
   }

    if (textures[0] != 0)
    {
        glDeleteTextures(ARRAY_SIZE_IN_ELEMENTS(textures), textures);
    }
    
    if (depthTexture != 0)
    {
        glDeleteTextures(1, &depthTexture);
    }
}

bool GBuffer::Initialize(int screenWidth, int screenHeight)
{
    // fbo
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    
    // tex gen
    glGenTextures(ARRAY_SIZE_IN_ELEMENTS(textures), textures);
    glGenTextures(1, &depthTexture);
    
    // gbuffer
    for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(textures); i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, screenWidth, screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);
    }
    
    // depth
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, screenWidth, screenHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    
    glDrawBuffers(ARRAY_SIZE_IN_ELEMENTS(drawBuffers), drawBuffers);
    
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        LogError("Frame Buffer Error");
        return false;
    }
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    return true;
    
}

void GBuffer::BindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void GBuffer::BindForReading()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(textures); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
    }
    
}

void GBuffer::TestBind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
}

void GBuffer::SetReadBuffer(GBUFFER_TEXTURE_TYPE gBufferTextureType)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + gBufferTextureType);
}