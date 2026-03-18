//
// Created by radov on 08.03.2026.
//


#pragma once

#include <Core/Log/Log.h>

#ifdef PLATFORM_WINDOWS
#define DEBUG_BREAK() __debugbreak();
#endif
#ifdef PLATFORM_MAC
#define DEBUG_BREAK() __builtin_debugtrap();
#endif

#define Unimplemented() do {LOG_ERROR("This function is unimplemented, please implement"); DEBUG_BREAK();} while(0);
#define Assert(x) do { if(!(x)) { LOG_ERROR("Assert failed: " #x); DEBUG_BREAK(); } } while(0)
#define NoEntry() do {LOG_ERROR("No entry here"); DEBUG_BREAK();} while(0);
