//
// Created by radov on 18.03.2026.
//

#include "Level.h"
#include "App.h"
#include "EventHandler.h"
#include "ECS/Systems/DebugDrawTransformSystem.h"
#include "ECS/Systems/DebugDrawUISystem.h"
#include "ECS/Systems/DebugStatsSystem.h"

Level::Level()
{
    Textures = std::make_unique<TextureManager>(App::Get().GetRenderer());
    Fonts = std::make_unique<FontManager>();
}

void Level::OnUpdate(float DeltaTime)
{
    CurrentRegistry.RunSystems(SystemPhase::Physics,DeltaTime);
    CurrentRegistry.RunSystems(SystemPhase::Update,DeltaTime);
    CurrentRegistry.RunSystems(SystemPhase::PostUpdate,DeltaTime);

#ifdef SE_DEBUG
    if (EventHandler::IsKeyPressed(SDLK_F1))
    {
        if (CurrentRegistry.HasSystem<DebugDrawTransformSystem>())
        {
            LOG_INFO("Transform debug turned OFF");
            CurrentRegistry.RemoveSystem<DebugDrawTransformSystem>();
        }else
        {
            LOG_INFO("Transform debug turned ON");
            CurrentRegistry.AddSystem<DebugDrawTransformSystem>(App::Get().GetRenderer());
        }
    }

    if (EventHandler::IsKeyPressed(SDLK_F2))
    {
        if (CurrentRegistry.HasSystem<DebugDrawUISystem>())
        {
            LOG_INFO("UI debug turned OFF");
            CurrentRegistry.RemoveSystem<DebugDrawUISystem>();
        }else
        {
            LOG_INFO("UI debug turned ON");
            CurrentRegistry.AddSystem<DebugDrawUISystem>(App::Get().GetRenderer());
        }
    }

    if (EventHandler::IsKeyPressed(SDLK_F3))
    {
        if (CurrentRegistry.HasSystem<DebugStatsSystem>())
        {
            LOG_INFO("Debug stats turned OFF");
            CurrentRegistry.RemoveSystem<DebugStatsSystem>();
        }else
        {
            LOG_INFO("Debug stats turned ON");
            CurrentRegistry.AddSystem<DebugStatsSystem>(App::Get().GetRenderer());
        }
    }
#endif

}

void Level::OnRender(const Renderer &Renderer,float DeltaTime)
{
    CurrentRegistry.RunSystems(SystemPhase::Render,DeltaTime);
    CurrentRegistry.RunSystems(SystemPhase::RenderUI,DeltaTime);
#ifdef SE_DEBUG
    CurrentRegistry.FlushTimings();
#endif
}

void Level::OnExit()
{

}
