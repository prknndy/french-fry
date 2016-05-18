//
//  Renderer.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/13/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Renderer__
#define __GLFramework__Renderer__

#include <GL/glew.h>

#include "Math3D.h"
#include "Camera.h"
#include "Mesh.h"

class Renderer
{
    int screenWidth;
    int screenHeight;
    Camera* currentCamera;
    
    Matrix4f wvp;
    Renderer();
    static Renderer* instance;
public:
    static Renderer* GetInstance() {
        if (instance == NULL)
        {
            instance = new Renderer();
        }
        return instance;
    }
    void Initialize(int _screenWidth, int screenHeight);
    void SetCamera(Camera* camera);
    void BeginRender();
    void RenderMesh(Mesh* mesh);
    void EndRender();
    
    Matrix4f& GetWVP();
};

#endif /* defined(__GLFramework__Renderer__) */
