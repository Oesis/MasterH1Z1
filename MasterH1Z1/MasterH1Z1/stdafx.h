#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#endif

#include <SDKDDKVer.h>

// C RunTime Header Files
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>

#include "Vector3.h"
#include "Patchable.h"
#include "Macros.h"
#include "StaticEnums.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

typedef unsigned int uint;
