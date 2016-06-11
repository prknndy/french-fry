//
//  TestApp.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__TestApp__
#define __GLFramework__TestApp__

#include "App.h"

class TestApp : public App
{
    Camera* camera;
    Model* model;
    Model* model2;
    Vector3 pos;//(0.0f, -50.0f, 200.0f);
    Vector3 rot;//(0.0f, 0.0f, 0.0f);
    Vector3 scale;//(0.25f, 0.25f, 0.25f);
    
    Vector3 pos2;
    Vector3 scale2;
    
    Model* model3;
    Mesh* mesh;
    Vector3 pos3;
    Vector3 rot3;
    Vector3 scale3;
    
    Skybox* skybox;
    
    DirectionalLight* dirLight;
    PointLight* pLight1;
    PointLight* pLight2;
    PointLight* pLight3;
    
    bool mouseMove;
    Vector2 lastMousePos;
    Vector3 cameraRot;
    float cameraOffset;
protected:
    virtual void PostInitialize();
    virtual void Update();
};

#endif /* defined(__GLFramework__TestApp__) */
