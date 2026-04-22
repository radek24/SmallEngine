//
// Created by radov on 22.04.2026.
//

#include "ParticleSystem.h"

#include <ECS/Registry.h>
#include "ECS/Components/ParticleComponent.h"
#include "ECS/Components/TransformComponent.h"

void ParticleSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    auto View = CurrentRegistry.MakeView<ParticleComponent, TransformComponent>();
    View.Each([&](Entity, ParticleComponent& PC, TransformComponent& TC)
    {
        PC.Velocity.Y += Gravity * PC.GravityScale * DeltaTime;
        float DampFactor = 1.0f - (1.0f - PC.Damping) * DeltaTime * 60.0f;
        PC.Velocity  = PC.Velocity * DampFactor;
        TC.Position += PC.Velocity * DeltaTime;
    });
}