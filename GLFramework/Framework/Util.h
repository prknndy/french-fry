//
//  Util.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/16/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Util__
#define __GLFramework__Util__

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

bool ReadFile(const char* fileName, string &outContents);

void LogError(const char* error);

void LogError(const char* error, const char* s);

void LogDebug(const char* str);

#endif /* defined(__GLFramework__Util__) */
