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
#include "GBuffer.h"
#include "Camera.h"
#include "Mesh.h"
#include "DRLightShader.h"

class Renderer
{
    int screenWidth;
    int screenHeight;
    Camera* currentCamera;
    
    GLuint vao;
    
    Matrix4f projTrans;
    Matrix4f viewTrans;
    Matrix4f vpTrans;
    Matrix4f worldTrans;
    Matrix4f wvp;
    Vector3 eyePos;
    
    // Deferred Rendering
    GBuffer gBuffer;
    DRLightShader drLightShader;
    Mesh quad;
    // temp
    DirectionalLight dirLight;
    PointLight pointLight;
    
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
    
    // Forward Rendering
    void BeginRender();
    void RenderMesh(Mesh* mesh);
    void EndRender();
    
    // Deferred Rendering
    void DRInitialize();
    void DRBeginGeometryPass();
    void DRLightPass();
    void DRBeginLightpass();
    void DRDirectionalLightPass();
    void DREndLightPass();
    
    void SetWorldTrans(Matrix4f* _worldTrans);
    void SetWorldTrans(Vector3 pos, Vector3 rot, Vector3 scale);
    
    Matrix4f& GetWVP();
    Matrix4f& GetWorldTrans();
    Vector3& GetEyePos();
    DirectionalLight& GetDirLight();
    PointLight& GetPointLight();
    
};

#endif /* defined(__GLFramework__Renderer__) */
