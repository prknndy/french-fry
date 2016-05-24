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
    Vector3 pos;//(0.0f, -50.0f, 200.0f);
    Vector3 rot;//(0.0f, 0.0f, 0.0f);
    Vector3 scale;//(0.25f, 0.25f, 0.25f);
    
    DirectionalLight* dirLight;
    PointLight* pLight1;
    PointLight* pLight2;
    PointLight* pLight3;
protected:
    virtual void PostInitialize();
    virtual void Update();
};

#endif /* defined(__GLFramework__TestApp__) */
