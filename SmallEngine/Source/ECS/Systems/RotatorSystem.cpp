//
// Created by Radovan Šťastný on 20.04.2026.
//

#include "RotatorSystem.h"

#include <ECS/Registry.h>

#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/TransformComponent.h"

void RotatorSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [DeltaTime](Entity E, TransformComponent &T,RotatorComponent &V)
    {
        T.Transform.Rotation += Rotator(DeltaTime*V.RotationSpeed);
    };
    CurrentRegistry.MakeView<TransformComponent,RotatorComponent>().Each(Callback);
}
