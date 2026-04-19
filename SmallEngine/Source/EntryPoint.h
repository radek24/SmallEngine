#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Engine/App.h"

extern App* CreateApplication();
#ifdef PLATFORM_WINDOWS || PLATFORM_MAC
int main(int argc, char *argv[])
{
    auto App = CreateApplication();
    App->SetArgs(argc,argv);
    App->Run();
    delete App;
    return 0;
}

#else
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout << "Unsupported platform" << std::endl;
    return 0;
}
#endif
