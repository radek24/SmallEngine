//
// Created by radov on 21.04.2026.
//

#include "DebugStatsSystem.h"

#include <ECS/Registry.h>
#include <Engine/Input/EventHandler.h>

void DebugStatsSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
#ifdef SE_DEBUG
    RendererRef->DrawRectangle(Vector2f(5,10),Vector2f(300,60),Color(0,0,0,0.5));
    const std::string FPS = std::format("FPS: {:.2f}", (1/DeltaTime));
    RendererRef->DrawDebugText(Vector2f(10,10),FPS.c_str(),Color(0.0f,1,0));

    const std::string Entities = std::format("Entites Alive: {}", CurrentRegistry.GetNumberOfEntities());
    RendererRef->DrawDebugText(Vector2f(10,20),Entities.c_str(),Color(0.0f,1,1));

    const std::string Systems = std::format("Systems Active: {}", CurrentRegistry.GetNumberOfSystems());
    RendererRef->DrawDebugText(Vector2f(10,30),Systems.c_str(),Color(1.0f,1,0));

    const std::string MousePos = std::format("MousePos: {}x {}y", EventHandler::GetMousePos().X,EventHandler::GetMousePos().Y);
    RendererRef->DrawDebugText(Vector2f(10,40),MousePos.c_str(),Color(1.0f,1,0));

    if(EventHandler::IsKeyPressed(SDLK_F4))
        ShowSystemTimings = !ShowSystemTimings;

    if(!ShowSystemTimings)
        return;

    RendererRef->DrawDebugText(Vector2f(10,60),"System timings",Color(0,1,0));

    auto Timings = CurrentRegistry.GetTimings();

    int i = 0;
    for(auto Timing : Timings)
    {
        const std::string SystemInfo = std::format("{}: {:.2f} ms",Timing.SystemName, Timing.Time);
        RendererRef->DrawRectangle(Vector2f(5,70 + (10*i)),Vector2f(300,10),Color(0,0,0,0.5));
        RendererRef->DrawDebugText(Vector2f(20,70 + (10*i)),SystemInfo.c_str(),Color(0,1,0));
        i++;
    }
#endif
}
