#pragma once
#include "ECS/System.h"
#include "Engine/Math/MathForward.h"

class PlayerLifecycleSystem : public System
{
public:
    explicit PlayerLifecycleSystem(
        Vector2f RespawnPos = {450.0f, 450.0f},
        float RespawnDelay = 2.0f,
        float InvincibleTime = 3.0f,
        float BlinkPeriod = 0.20f
    );

    void Update(Registry& CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::Update; }

private:
    Vector2f RespawnPos;
    float RespawnDelay;
    float InvincibleTime;
    float BlinkPeriod;
};