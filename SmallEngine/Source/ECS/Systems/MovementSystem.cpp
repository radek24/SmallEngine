//
// Created by radov on 19.04.2026.
//

#include "MovementSystem.h"

#include <ECS/Entity.h>
#include <ECS/Registry.h>
#include "ECS/Components/TransformComponent.h"

void MovementSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [](Entity E, TransformComponent &T)
    {
        T.Transform.Position.X += 0.1;
        LOG_INFO("{0}", T.Transform.Position);
    };
    CurrentRegistry.MakeView<TransformComponent>().Each(Callback);
}
