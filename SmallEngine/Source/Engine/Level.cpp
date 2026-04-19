//
// Created by radov on 18.03.2026.
//

#include "Level.h"
#include "App.h"

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
}

void Level::OnRender(const Renderer &Renderer,float DeltaTime)
{
    CurrentRegistry.RunSystems(SystemPhase::Render,DeltaTime);
    CurrentRegistry.RunSystems(SystemPhase::RenderUI,DeltaTime);
}

void Level::OnExit()
{

}
