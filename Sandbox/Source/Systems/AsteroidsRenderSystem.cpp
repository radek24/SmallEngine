#include "AsteroidsRenderSystem.h"

#include <cmath>
#include <ECS/Registry.h>
#include "ECS/Components/TransformComponent.h"
#include "Engine/Math/MathUtils.h"
#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/PlayerShipComponent.h"

void AsteroidsRenderSystem::DrawPolygon(Vector2f Center, float Radius, int Sides, Rotator Rot, Color C) const
{
    const float Step   = 2.0f * MathUtils::PI / static_cast<float>(Sides);
    const float RotRad = Rot.GetAngleRadians();
    for (int i = 0; i < Sides; ++i)
    {
        float A1 = i * Step + RotRad;
        float A2 = (i + 1) * Step + RotRad;
        Vector2f P1 = Center + Vector2f(cosf(A1) * Radius, sinf(A1) * Radius);
        Vector2f P2 = Center + Vector2f(cosf(A2) * Radius, sinf(A2) * Radius);
        RendererRef->DrawLine(P1, P2, 1.5f, C);
    }
}

void AsteroidsRenderSystem::DrawShip(Vector2f Center, Rotator Rot, Color C) const
{
    const float AngleRad = Rot.GetAngleRadians();
    const float Cos = cosf(AngleRad);
    const float Sin = sinf(AngleRad);

    Vector2f Fwd = { Sin,  -Cos};
    Vector2f Right = { Cos,   Sin};

    Vector2f Nose = Center + Fwd * 16.0f;
    Vector2f RightWing = Center - Fwd * 10.0f + Right * 11.0f;
    Vector2f LeftWing = Center - Fwd * 10.0f - Right * 11.0f;

    RendererRef->DrawLine(Nose, RightWing,1.5f, C);
    RendererRef->DrawLine(RightWing,LeftWing,1.5f, C);
    RendererRef->DrawLine(LeftWing,Nose,1.5f, C);
}

void AsteroidsRenderSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    CurrentRegistry.MakeView<TransformComponent, AsteroidComponent>().Each(
        [&](Entity, TransformComponent& TC, AsteroidComponent& AC)
        {
            int Sides = 8 + AC.Tier * 2;
            DrawPolygon(TC.Position, AC.Radius, Sides, TC.Rotation, Color(1.0f));
        });

    CurrentRegistry.MakeView<TransformComponent, BulletComponent>().Each(
        [&](Entity, TransformComponent& TC, BulletComponent&)
        {
            RendererRef->DrawFilledCircle(TC.Position, 3.5f, Color(0.4f, 1.0f, 1.0f));
        });

    CurrentRegistry.MakeView<TransformComponent, PlayerShipComponent>().Each(
        [&](Entity, TransformComponent& TC, PlayerShipComponent& PSC)
        {
            if (!PSC.ShipVisible)
                return;

            Color ShipColor = PSC.IsInvincible ? Color(0.5f, 0.8f, 1.0f) : Color(1.0f);
            DrawShip(TC.Position, TC.Rotation, ShipColor);

            if (PSC.IsThrustHeld)
            {
                const float A = TC.Rotation.GetAngleRadians();
                Vector2f Fwd = { sinf(A), -cosf(A) };
                Vector2f Right = { cosf(A),  sinf(A) };
                Vector2f ThrustTip = TC.Position - Fwd * 22.0f;
                Vector2f FlamL = TC.Position - Fwd * 10.0f + Right * 5.0f;
                Vector2f FlamR = TC.Position - Fwd * 10.0f - Right * 5.0f;
                RendererRef->DrawLine(FlamL, ThrustTip, 1.5f, Color(1.0f, 0.6f, 0.0f));
                RendererRef->DrawLine(FlamR, ThrustTip, 1.5f, Color(1.0f, 0.6f, 0.0f));
            }
        });
}