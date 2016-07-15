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
#include <vector>

#include "Math3D.h"
#include "GBuffer.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
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
    bool isInDR;
    
    // Lights
    DirectionalLight* dirLight;
    
    std::vector<PointLight*> pointLights;
    
    
    
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
    
    void RenderModel(Model* model);
    void RenderMesh(Mesh* mesh);
    void RenderMesh(Mesh* mesh, Material* mat);
    
    void RenderSkybox(Mesh* mesh, Material* mat);
    
    // Forward Rendering
    void BeginRender();
    void EndRender();
    
    // Deferred Rendering
    void DRInitialize();
    void DRBeginGeometryPass();
    void DRLightPass();
    void DRBeginLightpass();
    void DRDirectionalLightPass();
    void DRPointLightPass();
    void DREndLightPass();
    
    // Lighting
    void SetDirectionLight(DirectionalLight* _dirLight);
    void AddPointLight(PointLight* pointLight);
    void RemovePointLight(PointLight* pointLight);
    
    void SetWorldTrans(Matrix4f* _worldTrans);
    void SetWorldTrans(Vector3 pos, Vector3 rot, Vector3 scale);
    
    Matrix4f& GetWVP();
    Matrix4f& GetWorldTrans();
    Vector3& GetEyePos();
    DirectionalLight& GetDirLight();
    PointLight& GetPointLight(int index);
    int GetPointLightCount();
    
};

#endif /* defined(__GLFramework__Renderer__) */
