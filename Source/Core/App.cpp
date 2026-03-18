//
// Created by Radovan Šťastný on 09.03.2026.
//

#include "App.h"

#include <Core/Log/Log.h>

#include "DebugBreaks.h"
#include "EventHandler.h"

static App* Application = nullptr;

App::App(const Specifications &AppSpec)
{
    Application = this;
    Log::Initialize();
    AppSpecification = AppSpec;
    FrameCounter = 0;
    AppWindow = Window::Create(AppSpec.WindowSpecs);
    AppRenderer = Renderer::Create(*AppWindow);
    Running = true;
}

void App::Run()
{
    SDL_Event e;
    while(Running)
    {
        EventHandler::PollInputs();
        if(EventHandler::ShouldStop())
            Stop();

        if (AppWindow->ShouldClose())
        {
            Stop();
            break;
        }
        AppRenderer->BeginFrame();

        Vector2f Pos(EventHandler::GetInputState().MousePos.X,EventHandler::GetInputState().MousePos.Y);
        Vector2f Size(50,50);
        Color Col(1,1,1);

        AppRenderer->DrawRectangle(Pos,Size,Col);

        AppRenderer->EndFrame();
    }
}

void App::Stop()
{
    Running = false;
}

App& App::Get()
{
    if (Application == nullptr)
        Assert("Called get on app before it was constructed");

    return *Application;
}

float App::GetTime()
{
    Unimplemented();
    return 0;
}

void App::PrintInfo()
{
    LOG_INFO("Info about app:");
    LOG_INFO("So far no info.");
}
