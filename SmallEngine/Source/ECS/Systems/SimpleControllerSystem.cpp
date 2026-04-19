//
// Created by radov on 19.04.2026.
//

#include "SimpleControllerSystem.h"

#include <ECS/Registry.h>
#include <Engine/EventHandler.h>

#include "ECS/Components/SimpleKeyboardControllerComponent.h"
#include "ECS/Components/TransformComponent.h"


void SimpleControllerSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto ControllerCallback = [DeltaTime](Entity E, SimpleKeyboardControllerComponent& SKCC, TransformComponent& TC)
    {
        if(EventHandler::IsKeyHeld(SDLK_W))
            TC.Transform.Position.Y -= SKCC.Speed * DeltaTime;
        if(EventHandler::IsKeyHeld(SDLK_S))
            TC.Transform.Position.Y += SKCC.Speed * DeltaTime;
        if(EventHandler::IsKeyHeld(SDLK_A))
            TC.Transform.Position.X -= SKCC.Speed * DeltaTime;
        if(EventHandler::IsKeyHeld(SDLK_D))
            TC.Transform.Position.X += SKCC.Speed * DeltaTime;
    };
    CurrentRegistry.MakeView<SimpleKeyboardControllerComponent,TransformComponent>().Each(ControllerCallback);
}
