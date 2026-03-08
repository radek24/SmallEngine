#include <iostream>

#include "Log/Log.h"

int main()
{
    Log::Initialize();
    LOG_INFO("Test");
    return 0;
}
