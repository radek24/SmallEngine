//
// Created by radov on 18.03.2026.
//

#pragma once

#ifdef _WIN32
    #ifdef SE_BUILD_DLL
        #define SE_API __declspec(dllexport)
    #elif defined(SE_DLL)
        #define SE_API __declspec(dllimport)
    #else
        #define SE_API
    #endif
#else
    #define SE_API __attribute__((visibility("default")))
#endif


#define ENGINE_VERSION_MAJOR 0
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_PATCH 0

#define STRINGIFY(x)  #x
#define TOSTRING(x)   STRINGIFY(x)

#define ENGINE_VERSION \
TOSTRING(ENGINE_VERSION_MAJOR) "." \
TOSTRING(ENGINE_VERSION_MINOR) "." \
TOSTRING(ENGINE_VERSION_PATCH)


#include "Engine/Log/Log.h"
