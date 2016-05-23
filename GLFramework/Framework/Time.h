//
//  Time.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Time__
#define __GLFramework__Time__

class Time
{
    double lastFrameTime;
    double deltaTime;
    static Time* instance;
    Time();
public:
    static Time* GetInstance()
    {
        if (instance == NULL)
        {
            instance = new Time();
        }
        return instance;
    }
    void Update();
    double DeltaTime();
};

#endif /* defined(__GLFramework__Time__) */
