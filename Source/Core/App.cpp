//
// Created by Radovan Šťastný on 09.03.2026.
//

#include "App.h"

#include <Log/Log.h>

#include "DebugBreaks.h"

static App* Application = nullptr;

App::App(const Specifications &AppSpec)
{
    Application = this;
    Log::Initialize();
    AppSpecification = AppSpec;
    FrameCounter = 0;

}

App& App::Get()
{
    if (Application == nullptr){Assert("Called get on app before it was constructed");}
    return *Application;
}

float App::GetTime()
{
    Unimplemented();
}

void App::PrintInfo()
{
    LOG_INFO("Info about app:");
    LOG_INFO("So far no info.");
}
