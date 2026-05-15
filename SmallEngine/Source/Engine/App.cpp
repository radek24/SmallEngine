//
// Created by Radovan Šťastný on 09.03.2026.
//

#include "App.h"

#include <Engine/Log/Log.h>
#include <SDL_image/include/SDL3_image/SDL_image.h>

#include "DebugBreaks.h"
#include "Input/EventHandler.h"

static App* Application = nullptr;

void App::Init(const Specifications &AppSpec)
{
    Application = this;
    Log::Initialize();
    AppSpecification = AppSpec;
    FrameCounter = 0;
    AppWindow = Window::Create(AppSpec.WindowSpecs);
    AppRenderer = Renderer::Create(*AppWindow);
    AppSoundManager = std::make_unique<SoundManager>();
    SignalManager = std::make_unique<class SignalManager>();
    Settings = std::make_unique<SettingManager>();
    Settings->LoadFromDefaultConfig(AppSpec.SettingConfigPath);
    Settings->LoadConfig(AppSpec.SettingPath);
    Running = true;
    PrintInfo();
}

App::~App()
{

}

void App::Run()
{
    Assert(LevelToTransitionTo != nullptr);

    float LastTime = GetTime();
    while(Running)
    {
        const float CurrentTime = GetTime();
        float DeltaTime = CurrentTime - LastTime;
        LastTime = CurrentTime;
        TryToTransitionToLevel();
        EventHandler::PollInputs();
        if(EventHandler::ShouldStop())
        {
            Stop();
            break;
        }
        CurrentLevel->OnUpdate(DeltaTime);
        AppRenderer->BeginFrame();
        CurrentLevel->OnRender(*AppRenderer,DeltaTime);
        AppRenderer->EndFrame();
        EventHandler::Cleanup();
        FrameCounter++;
    }
}

void App::Stop()
{
    LOG_INFO("Unloading level");
    CurrentLevel->OnExit();
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
    return static_cast<float>(static_cast<double>(SDL_GetTicks()) / 1000.0);
}

void App::SetArgs(int argc, char *argv[])
{
    AppSpecification.ArgumentCount = argc;
    AppSpecification.Arguments = argv;
}

void App::TryToTransitionToLevel()
{
    if(!LevelToTransitionTo)
        return;
    
    if(CurrentLevel)
    {
        LOG_INFO("Unloading level");
        CurrentLevel->OnExit();
        CurrentLevel.reset();

    }
    CurrentLevel = std::move(LevelToTransitionTo);
    LOG_INFO("Loading level");
    CurrentLevel->OnEnter();
}

Level * App::GetCurrentLevel() const
{
    return CurrentLevel.get();
}

void App::PrintInfo()
{
    int Version = SDL_GetVersion();
    LOG_INFO("SDL Version : {0}.{1}.{2}",SDL_VERSIONNUM_MAJOR(Version),SDL_VERSIONNUM_MINOR(Version),SDL_VERSIONNUM_MICRO(Version));
    #ifdef SE_DEBUG
        LOG_INFO("This is debug build");
    #endif
    LOG_INFO("Engine Version: {0}", ENGINE_VERSION);

}
