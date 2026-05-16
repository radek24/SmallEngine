#include "PlayerLifecycleSystem.h"

#include <cmath>
#include <ECS/Registry.h>
#include "ECS/Components/TransformComponent.h"
#include "../Components/PlayerShipComponent.h"
#include "../Components/VelocityComponent.h"

PlayerLifecycleSystem::PlayerLifecycleSystem(
    Vector2f RespawnPos, float InvincibleTime, float BlinkPeriod)
    : RespawnPos(RespawnPos)
    , InvincibleTime(InvincibleTime)
    , BlinkPeriod(BlinkPeriod)
{}

void PlayerLifecycleSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    CurrentRegistry.MakeView<TransformComponent, VelocityComponent, PlayerShipComponent>().Each(
        [&](Entity, TransformComponent& TC, VelocityComponent& VC, PlayerShipComponent& PSC)
        {
            if (PSC.IsDead)
            {
                PSC.ShipVisible = false;
                PSC.RespawnTimer -= DeltaTime;

                if (PSC.RespawnTimer <= 0.0f)
                {
                    PSC.IsDead = false;
                    PSC.IsInvincible = true;
                    PSC.InvincibleTimer = InvincibleTime;
                    PSC.ShipVisible = true;
                    TC.Position = RespawnPos;
                    TC.Rotation = Rotator(0.0f);
                    VC.Velocity= {0.0f, 0.0f};
                }
                return;
            }

            if (PSC.IsInvincible)
            {
                PSC.InvincibleTimer -= DeltaTime;
                float Phase = fmodf(PSC.InvincibleTimer, BlinkPeriod);
                PSC.ShipVisible = Phase > BlinkPeriod * 0.5f;

                if (PSC.InvincibleTimer <= 0.0f)
                {
                    PSC.IsInvincible = false;
                    PSC.ShipVisible = true;
                }
                return;
            }

            PSC.ShipVisible = true;
        });
}