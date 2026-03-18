#include <iostream>

#include "Core/Log/Log.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Core/App.h"
#include "Core/Specifications.h"

#include "Core/Math/MathForward.h"

int main(int argc, char *argv[])
{

    Specifications AppSpec;
    AppSpec.ArgumentCount = argc;
    AppSpec.Arguments = argv;
    AppSpec.AppName = "Small Engine";
    AppSpec.WindowSpecs.Width = 500;
    AppSpec.WindowSpecs.Height = 500;
    AppSpec.WindowSpecs.Name = "Small Engine";

    App application(AppSpec);
    //application.LoadLevel("test.json");
    application.Run();
    return 0;
}
