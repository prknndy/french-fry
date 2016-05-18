//
//  Camera.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/12/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Camera__
#define __GLFramework__Camera__

#include "Math3D.h"

class Camera
{
    Vector3 location;
    Vector3 up;
    Vector3 forward;

public:
    Camera(Vector3 _location, Vector3 _up, Vector3 _forward);
    Vector3 GetLocation() { return location; };
    Vector3 GetUp() { return up; };
    Vector3 GetForward() { return forward; };
    
};

#endif /* defined(__GLFramework__Camera__) */
