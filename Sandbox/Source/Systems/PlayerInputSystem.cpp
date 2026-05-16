#include "PlayerInputSystem.h"

#include <cmath>
#include <ECS/Registry.h>
#include <Engine/App.h>
#include <Engine/Input/EventHandler.h>
#include "Engine/Math/Rotator.h"
#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "../AsteroidsSignals.h"
#include "../Components/BulletComponent.h"
#include "../Components/PlayerShipComponent.h"
#include "../Components/VelocityComponent.h"

PlayerInputSystem::PlayerInputSystem(float RotationSpeed, float ThrustForce, float BulletSpeed, float FireCooldown)
    : RotationSpeed(RotationSpeed), ThrustForce(ThrustForce), BulletSpeed(BulletSpeed), FireCooldown(FireCooldown)
{}

void PlayerInputSystem::SpawnBullet(Registry& R, Vector2f Pos, Rotator Rot) const
{
    const float A = Rot.GetAngleRadians();
    Vector2f Fwd  = {sinf(A), -cosf(A)};
    Entity E = R.CreateEntity();
    R.AddComponent<TransformComponent>(E, TransformComponent{Pos + Fwd * 20.0f});
    R.AddComponent<VelocityComponent>(E, VelocityComponent{Fwd * BulletSpeed});
    R.AddComponent<BulletComponent>(E, BulletComponent{});
    R.AddComponent<LifetimeComponent>(E, LifetimeComponent{1.5f});
    App::Get().GetSignalManager()->Dispatch(Signal_BulletFired, SignalPayload::GetEmpty());
}

void PlayerInputSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    CurrentRegistry.MakeView<TransformComponent, VelocityComponent, PlayerShipComponent>().Each(
        [&](Entity, TransformComponent& TC, VelocityComponent& VC, PlayerShipComponent& PSC)
        {
            PSC.IsThrustHeld = false;

            if (PSC.IsDead)
                return;

            if (EventHandler::IsKeyHeld(SDLK_LEFT)  || EventHandler::IsKeyHeld(SDLK_A))
                TC.Rotation -= Rotator(RotationSpeed * DeltaTime);
            if (EventHandler::IsKeyHeld(SDLK_RIGHT) || EventHandler::IsKeyHeld(SDLK_D))
                TC.Rotation += Rotator(RotationSpeed * DeltaTime);

            PSC.IsThrustHeld = EventHandler::IsKeyHeld(SDLK_UP) || EventHandler::IsKeyHeld(SDLK_W);
            if (PSC.IsThrustHeld)
            {
                const float A = TC.Rotation.GetAngleRadians();
                VC.Velocity += Vector2f(sinf(A), -cosf(A)) * ThrustForce * DeltaTime;
            }

            PSC.FireCooldown -= DeltaTime;
            if (EventHandler::IsKeyPressed(SDLK_SPACE) && PSC.FireCooldown <= 0.0f)
            {
                SpawnBullet(CurrentRegistry, TC.Position, TC.Rotation);
                PSC.FireCooldown = FireCooldown;
            }
        });
}