//
//  main.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 4/22/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "TestApp.h"


int main(int argc, const char * argv[])
{
    TestApp* testApp = new TestApp();
    testApp->Initialize(1052, 512);
    
    while (testApp->IsActive())
    {
        testApp->RenderUpdate();
    }
    
    return 0;
}

