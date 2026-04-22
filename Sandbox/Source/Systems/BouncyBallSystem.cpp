//
// Created by radov on 20.04.2026.
//

#include "BouncyBallSystem.h"
#include <ECS/Registry.h>
#include <Engine/EventHandler.h>

#include "../Components/BouncyBallComponent.h"
#include "ECS/Components/TransformComponent.h"

void BouncyBallSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    constexpr float Gravity = 980.0f;
    constexpr float MouseRadius = 200.0f;
    constexpr float MouseRadiusSq = MouseRadius * MouseRadius;
    constexpr float MouseForce = 10000.0f;

    const auto WinWidth = static_cast<float>(CurrentWindow->GetWidth());
    const auto WinHeight = static_cast<float>(CurrentWindow->GetHeight());
    const auto MousePos= EventHandler::GetMousePos();
    const bool Repel = EventHandler::IsMouseButtonHeld(MouseButton::Left);
    const bool Attract = EventHandler::IsMouseButtonHeld(MouseButton::Right);
    const bool MouseActive = Repel || Attract;
    const float GravityDT = Gravity * DeltaTime;
    const float ForceDT = MouseForce * DeltaTime;
    const float ForceSign = Repel ? -1.0f : 1.0f;

    auto Callback = [this, DeltaTime, WinWidth, WinHeight, MousePos,MouseActive, MouseRadiusSq, GravityDT, ForceDT, ForceSign]
    (Entity E, BouncyBallComponent &BBC, TransformComponent &T)
    {
        const float Size = BBC.Size * T.Scale.X;

        if (MouseActive)
        {
            const Vector2f ToMouse    = MousePos - T.Position;
            const float    DistanceSq = ToMouse.LengthSquared();

            if (DistanceSq < MouseRadiusSq && DistanceSq > 0.01f)
            {
                const float Distance  = std::sqrt(DistanceSq);
                const float Falloff   = 1.0f - (Distance / MouseRadius);
                BBC.Velocity += (ToMouse / Distance) * (ForceDT * Falloff * ForceSign);
            }
        }

        BBC.Velocity.Y += GravityDT;
        T.Position += BBC.Velocity * DeltaTime;

        if (T.Position.Y + Size >= WinHeight)
        {
            T.Position.Y   = WinHeight - Size;
            BBC.Velocity.Y = -BBC.Velocity.Y * BBC.Damping;
            if (std::abs(BBC.Velocity.Y) < 20.0f)
                BBC.Velocity.Y = 0.0f;
        }
        else if (T.Position.Y - Size <= 0.0f)
        {
            T.Position.Y   = Size;
            BBC.Velocity.Y = -BBC.Velocity.Y * BBC.Damping;
        }

        if (T.Position.X + Size >= WinWidth)
        {
            T.Position.X   = WinWidth - Size;
            BBC.Velocity.X = -BBC.Velocity.X * BBC.Damping;
        }
        else if (T.Position.X - Size <= 0.0f)
        {
            T.Position.X   = Size;
            BBC.Velocity.X = -BBC.Velocity.X * BBC.Damping;
        }
    };

    CurrentRegistry.MakeView<BouncyBallComponent, TransformComponent>().Each(Callback);
}
