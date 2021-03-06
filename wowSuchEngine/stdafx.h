// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>

// C Runtime
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <iso646.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

// C++ Runtime
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// FMOD Audio Runtime
#include <fmod.hpp>

// GLFW, GL, and GLu
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// FreeType
#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>
