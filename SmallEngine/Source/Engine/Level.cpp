//
// Created by radov on 18.03.2026.
//

#include "Level.h"

void Level::OnUpdate(float DeltaTime)
{
    CurrentRegistry.RunSystems(SystemPhase::Physics,DeltaTime);
    CurrentRegistry.RunSystems(SystemPhase::Update,DeltaTime);
}

void Level::OnRender(const Renderer &Renderer,float DeltaTime)
{
    CurrentRegistry.RunSystems(SystemPhase::Render,DeltaTime);
}

void Level::OnExit()
{

}
