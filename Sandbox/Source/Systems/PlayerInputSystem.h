#pragma once
#include "ECS/System.h"
#include "Engine/Math/MathForward.h"
#include "Engine/Math/Rotator.h"

class PlayerInputSystem : public System
{
public:
    explicit PlayerInputSystem(
        float RotationSpeed = 180.0f,
        float ThrustForce = 280.0f,
        float BulletSpeed = 520.0f,
        float FireCooldown = 0.25f
    );

    void Update(Registry& CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::Update; }

private:
    float RotationSpeed;
    float ThrustForce;
    float BulletSpeed;
    float FireCooldown;

    void SpawnBullet(Registry& R, Vector2f Pos, Rotator Rot) const;
};