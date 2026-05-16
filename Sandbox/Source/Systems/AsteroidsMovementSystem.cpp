#include "AsteroidsMovementSystem.h"

#include <ECS/Registry.h>
#include "ECS/Components/TransformComponent.h"
#include "../Components/VelocityComponent.h"

void AsteroidsMovementSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    const float W = static_cast<float>(CurrentWindow->GetLogicalWidth());
    const float H = static_cast<float>(CurrentWindow->GetLogicalHeight());
    constexpr float Pad = 50.0f;

    CurrentRegistry.MakeView<TransformComponent, VelocityComponent>().Each(
        [&](Entity, TransformComponent& TC, VelocityComponent& VC)
        {
            const float Speed = VC.Velocity.Length();
            if (Speed > MaxSpeed && Speed > 0.0001f)
                VC.Velocity = VC.Velocity * (MaxSpeed / Speed);

            TC.Position += VC.Velocity * DeltaTime;

            if (TC.Position.X < -Pad)  TC.Position.X = W + Pad;
            else if (TC.Position.X > W + Pad) TC.Position.X = -Pad;
            if (TC.Position.Y < -Pad)  TC.Position.Y = H + Pad;
            else if (TC.Position.Y > H + Pad) TC.Position.Y = -Pad;
        });
}