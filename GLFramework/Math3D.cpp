//
//  Math3D.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/12/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include <math.h>
#include "Math3D.h"

void Matrix4f::CreateIdentity()
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::CreateTranslate(Vector3 trans)
{
   CreateIdentity();
   m[0][3] = trans.x;
   m[1][3] = trans.y;
   m[2][3] = trans.z;
}

void Matrix4f::CreateRotation(Vector3 rot)
{
    Matrix4f xRot, yRot, zRot;
    xRot.CreateIdentity();
    yRot.CreateIdentity();
    zRot.CreateIdentity();
    
    float x = ToRadian(rot.x);
    float y = ToRadian(rot.y);
    float z = ToRadian(rot.z);
    
    xRot.m[1][1] = cosf(x);
    xRot.m[1][2] = -sinf(x);
    xRot.m[2][1] = sinf(x);
    xRot.m[2][2] = cosf(x);
    
    yRot.m[0][0] = cosf(y);
    yRot.m[0][2] = -sinf(y);
    yRot.m[2][0] = sinf(y);
    yRot.m[2][2] = cosf(y);
    
    zRot.m[0][0] = cosf(z);
    zRot.m[0][1] = -sinf(z);
    zRot.m[1][0] = sinf(z);
    zRot.m[1][1] = cosf(z);

    *this = zRot * yRot * xRot;
}

void Matrix4f::CreateScale(Vector3 scale)
{
    CreateIdentity();
    m[0][0] = scale.x;
    m[1][1] = scale.y;
    m[2][2] = scale.z;
    m[3][3] = 1.0f;
}

void Matrix4f::CreateWVP(Vector3 forward, Vector3 up)
{
    Vector3 N = forward;
    N.Normalize();
    Vector3 U = up;
    U.Normalize();
    U = U.Cross(forward);
    Vector3 V = N.Cross(U);
    
    m[0][0] = U.x; m[0][1] = U.y; m[0][2] = U.z; m[0][3] = 0.0f;
    m[1][0] = V.x; m[1][1] = V.y; m[1][2] = V.z; m[1][3] = 0.0f;
    m[2][0] = N.x; m[2][1] = N.y; m[2][2] = N.z; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4f::CreateProj(int screenWidth, int screenHeight, float fov, float nearPlane, float farPlane)
{
    float aspectRatio = screenWidth / screenHeight;
    float planeRange = nearPlane - farPlane;
    float tanHFOV = tanf(ToRadian(fov / 2.0f));
    CreateIdentity();
    m[0][0] = 1.0f / (tanHFOV * aspectRatio);
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[0][3] = 0.0f;
    
    m[1][0] = 0.0f;
    m[1][1] = 1.0f / tanHFOV;
    m[1][2] = 0.0f;
    m[1][3] = 0.0f;
    
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = (-nearPlane - farPlane) / planeRange;
    m[2][3] = 2.0f * farPlane * nearPlane / planeRange;
    
    m[3][0] = 0.0f;
    m[3][1] = 0.0f;
    m[3][2] = 1.0f;
    m[3][3] = 0.0f;
}

