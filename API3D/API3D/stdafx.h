// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <math.h>

#include "cVector3.h"
#include "cMatrix.h"

using namespace std;
extern HWND g_hWnd;
#define PI 3.141592f
// TODO: reference additional headers your program requires here