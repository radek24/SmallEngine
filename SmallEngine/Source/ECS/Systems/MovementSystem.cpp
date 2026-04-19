//
// Created by radov on 19.04.2026.
//

#include "MovementSystem.h"

#include <ECS/Entity.h>
#include <ECS/Registry.h>
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/VelocityComponent.h"

void MovementSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [DeltaTime](Entity E, TransformComponent &T,VelocityComponent &V)
    {
        T.Transform.Position.X += V.Velocity.X * DeltaTime;
        T.Transform.Position.Y += V.Velocity.Y* DeltaTime;
    };
    CurrentRegistry.MakeView<TransformComponent,VelocityComponent>().Each(Callback);
}
