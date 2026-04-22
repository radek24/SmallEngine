//
// Created by radov on 22.04.2026.
//

#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"

/** Moves entities by their ParticleComponent velocity, applies gravity and damping each frame */
class SE_API ParticleSystem : public System
{
public:
    explicit ParticleSystem(float Gravity = 200.0f) : Gravity(Gravity) {}
    void Update(Registry& CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::Update; }
private:
    float Gravity;
};