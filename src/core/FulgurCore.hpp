#pragma once

#ifdef _WIN32
#ifdef FULGUR_EXPORTS
#define FGAPI __declspec(dllexport)
#else
#define FGAPI __declspec(dllimport)
#endif
#else
#define FGAPI
#endif

#include "glad.h"
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
