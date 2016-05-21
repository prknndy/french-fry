//
//  Lighting.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/20/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Lighting__
#define __GLFramework__Lighting__

#include "Math3D.h"

class Light
{
public:
    Vector3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    
    Light() : Color(0, 0, 0) {
        
    };
};

class DirectionalLight : public Light
{
public:
    Vector3 Direction;
    
    DirectionalLight() : Direction(0, 0, 0)
    {
        
    };
};

#endif /* defined(__GLFramework__Lighting__) */
