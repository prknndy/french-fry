//
//  Math3D.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/12/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef GLFramework_Math3D_h
#define GLFramework_Math3D_h

#include <math.h>

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

struct Vector2 {
    float x;
    float y;
    
public:
    Vector2()
    {
        x = 0;
        y = 0;
    }
    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    
};

struct Vector3 {
    float x;
    float y;
    float z;
    
public:
    
    Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    Vector3(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    Vector3 Cross(const Vector3& v) const
    {
        const float _x = y * v.z - z * v.y;
        const float _y = z * v.x - x * v.z;
        const float _z = x * v.y - y * v.x;
        
        return Vector3(_x, _y, _z);
    }
    
    
    Vector3& Normalize()
    {
        const float Length = sqrtf(x * x + y * y + z * z);
        
        x /= Length;
        y /= Length;
        z /= Length;
        
        return *this;
    }
    
    void Rotate(float angle, const Vector3& axis);
    
};

struct Vertex {
    Vector3 pos;
    Vector3 color;
    Vector2 uv;
    Vector3 normal;
    
    Vertex(Vector3 _pos, Vector3 _color, Vector2 _uv, Vector3 _normal) : pos(_pos), color(_color), uv(_uv), normal(_normal)
    {
        
    }
    
};

class Matrix4f {
public:
    float m[4][4];
    
public:
    void CreateIdentity();
    void CreateTranslate(Vector3 trans);
    void CreateRotation(Vector3 rot);
    void CreateScale(Vector3 scale);
    void CreateProj(int screenWidth, int screenHeight, float fov, float nearPlane, float farPlane);
    void CreateWVP(Vector3 forward, Vector3 up);
    
    inline Matrix4f operator*(const Matrix4f& Right) const
    {
        Matrix4f Ret;
        for (unsigned int i = 0 ; i < 4 ; i++) {
            for (unsigned int j = 0 ; j < 4 ; j++) {
                Ret.m[i][j] = m[i][0] * Right.m[0][j] +
                m[i][1] * Right.m[1][j] +
                m[i][2] * Right.m[2][j] +
                m[i][3] * Right.m[3][j];
            }
        }
        
        return Ret;
    }
    
    inline Vector3 operator*(const Vector3& v) const
    {
        Vector3 r;
        r.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * 1.0f;
        r.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * 1.0f;
        r.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * 1.0f;
        //r.x = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * 1.0f;
        return r;
    }
    
    
};

#endif
