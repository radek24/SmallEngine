#include <iostream>

#include "Log/Log.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Core/App.h"
#include "Core/Specifications.h"
#include "ECS/Entity.h"
#include "ECS/Registry.h"
#include "Math/MathForward.h"

int main(int argc, char *argv[])
{
    Log::Initialize();
    Registry CurrentRegistry;

    Entity e = CurrentRegistry.CreateEntity();
    LOG_INFO("{}",e.GetId());

    Specifications AppSpec;
    AppSpec.ArgumentCount = argc;
    AppSpec.Arguments = argv;
    AppSpec.AppName = "Small Engine";
    AppSpec.WindowSpecs.Width = 500;
    AppSpec.WindowSpecs.Height = 500;

    App application(AppSpec);
    //application.LoadLevel("test.json");
    application.Run();
    return 0;
}
