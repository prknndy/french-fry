//
//  Util.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/16/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Util.h"

bool ReadFile(const char* fileName, string &outContents)
{
    ifstream f(fileName);
    
    bool ret = false;
    
    if (f.is_open())
    {
        string line;
        while (getline(f, line)) {
            outContents.append(line);
            outContents.append("\n");
        }
        
        f.close();
        
        ret = true;
    }
    else
    {
        // log error
    }
    
    return ret;
}

void LogError(const char* error)
{
    fprintf(stderr, "%s\n", error);
}

void LogDebug(const char* str)
{
    fprintf(stdout, "%s\n", str);
}

