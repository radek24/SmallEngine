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


#include "Engine/Log/Log.h"
