#include <iostream>

#include "Engine/Log/Log.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Engine/App.h"

#include "Engine/Math/MathForward.h"

extern App* CreateApplication();

int main(int argc, char *argv[])
{
    auto App = CreateApplication();
    App->Run();
    delete App;
    return 0;
}
