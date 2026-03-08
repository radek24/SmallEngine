#include <iostream>

#include "Log/Log.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "ECS/Entity.h"
#include "ECS/Registry.h"
#include "Math/MathForward.h"

int main(int argc, char *argv[])
{
    Log::Initialize();
    Registry CurrentRegistry;

    Entity e = CurrentRegistry.CreateEntity();
    LOG_INFO("{}",e.GetId());


    return 0;
}
