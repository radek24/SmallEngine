#pragma once
#include <random>
#include "ECS/System.h"
#include "Engine/Core.h"
#include "Engine/Rendering/TextureManager.h"

class AsteroidsCollisionSystem : public System
{
public:
    explicit AsteroidsCollisionSystem(
        TextureHandle ParticleTexture,
        float ShipRadius   = 13.0f,
        float BulletRadius = 3.5f
    );

    void Update(Registry& CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::PostUpdate; }

private:
    TextureHandle ParticleTexture;
    float ShipRadius;
    float BulletRadius;
    std::mt19937 RNG;

    void SpawnExplosion(Registry& R, Vector2f Pos, int Tier);
    void SpawnChildAsteroid(Registry& R, Vector2f Pos, int Tier);
};