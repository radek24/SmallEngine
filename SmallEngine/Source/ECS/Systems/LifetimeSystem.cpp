//
// Created by radov on 19.04.2026.
//

#include "LifetimeSystem.h"

#include <ECS/Entity.h>
#include <ECS/Registry.h>

#include "ECS/Components/LifetimeComponent.h"

void LifetimeSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    std::vector<Entity> ToDestroy;

    auto Callback = [&ToDestroy,DeltaTime](Entity E, LifetimeComponent &LC)
    {
        LC.RemainingSeconds -= DeltaTime;
        if(LC.RemainingSeconds <= 0.0f)
            ToDestroy.push_back(E);
    };
    CurrentRegistry.MakeView<LifetimeComponent>().Each(Callback);

    for (auto E : ToDestroy)
        CurrentRegistry.DestroyEntity(E);
}

