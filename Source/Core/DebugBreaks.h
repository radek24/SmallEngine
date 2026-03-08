//
// Created by radov on 08.03.2026.
//


#pragma once

#include <Log/Log.h>

#define unimplemented() do {LOG_ERROR("This function is unimplemented, please implement"); __debugbreak();} while(0);
#define assert(x) do { if(!(x)) { LOG_ERROR("Assert failed: " #x); __debugbreak(); } } while(0)
#define no_entry() do {LOG_ERROR("No entry here"); __debugbreak();} while(0);