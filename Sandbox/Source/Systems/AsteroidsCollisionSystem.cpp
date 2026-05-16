#include "AsteroidsCollisionSystem.h"

#include <cmath>
#include <unordered_set>
#include <utility>
#include <vector>

#include <ECS/Registry.h>
#include <Engine/App.h>
#include "../AsteroidsSignals.h"
#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/ParticleComponent.h"
#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Rotator.h"
#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/PlayerShipComponent.h"
#include "../Components/VelocityComponent.h"

AsteroidsCollisionSystem::AsteroidsCollisionSystem(TextureHandle ParticleTexture, float ShipRadius, float BulletRadius)
    : ParticleTexture(ParticleTexture)
    , ShipRadius(ShipRadius)
    , BulletRadius(BulletRadius)
    , RNG(std::random_device{}())
{}

void AsteroidsCollisionSystem::SpawnExplosion(Registry& R, Vector2f Pos, int Tier)
{
    std::uniform_real_distribution<float> SpeedDist(40.0f + Tier * 25.0f, 80.0f + Tier * 40.0f);
    std::uniform_real_distribution<float> LifeDist(0.5f, 1.2f);
    std::uniform_real_distribution<float> HueDist(-15.0f, 15.0f);

    const int Count = 6 + Tier * 5;
    const float BaseHue = Tier == 3 ? 20.0f : (Tier == 2 ? 30.0f : 50.0f);

    for (int i = 0; i < Count; ++i)
    {
        Rotator Angle = (static_cast<float>(i) / Count) * 360.0f;
        float Speed = SpeedDist(RNG);

        Entity E = R.CreateEntity();
        R.AddComponent<TransformComponent>(E, TransformComponent{.Position = Pos, .Scale = {0.08f, 0.08f}});
        R.AddComponent<SpriteComponent>(E, SpriteComponent{.Texture = ParticleTexture,.Tint = Color::FromHSV(BaseHue + HueDist(RNG), 0.9f, 1.0f)});
        R.AddComponent<ParticleComponent>(E, ParticleComponent{
            .Velocity = {cosf(Angle.GetAngleRadians()) * Speed, sinf(Angle.GetAngleRadians()) * Speed},
            .Damping = 0.93f,
            .GravityScale = 0.0f
        });
        R.AddComponent<LifetimeComponent>(E, LifetimeComponent{LifeDist(RNG)});
    }
}

void AsteroidsCollisionSystem::SpawnChildAsteroid(Registry& R, Vector2f Pos, int Tier)
{
    std::uniform_real_distribution<float> AngleDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> SpeedDist(70.0f, 130.0f);
    std::uniform_real_distribution<float> SpinDist(-50.0f, 50.0f);

    Rotator A = AngleDist(RNG);
    float   S = SpeedDist(RNG);

    Entity E = R.CreateEntity();
    R.AddComponent<TransformComponent>(E, TransformComponent{Pos});
    R.AddComponent<VelocityComponent>(E, VelocityComponent{{cosf(A.GetAngleRadians()) * S, sinf(A.GetAngleRadians()) * S}});
    R.AddComponent<AsteroidComponent>(E, AsteroidComponent::FromTier(Tier));
    R.AddComponent<RotatorComponent>(E, RotatorComponent{SpinDist(RNG)});
}

void AsteroidsCollisionSystem::Update(Registry& CurrentRegistry, float)
{
    struct AstData { Entity E; Vector2f Pos; float Radius; int Tier; };
    struct BulData { Entity E; Vector2f Pos; };

    std::vector<AstData> Asteroids;
    std::vector<BulData> Bullets;

    CurrentRegistry.MakeView<TransformComponent, AsteroidComponent>().Each(
        [&](Entity E, TransformComponent& TC, AsteroidComponent& AC)
        { Asteroids.push_back({E, TC.Position, AC.Radius, AC.Tier}); });

    CurrentRegistry.MakeView<TransformComponent, BulletComponent>().Each(
        [&](Entity E, TransformComponent& TC, BulletComponent&)
        { Bullets.push_back({E, TC.Position}); });

    std::unordered_set<Entity> DeadBullets;
    std::unordered_set<Entity> DeadAsteroids;
    std::vector<std::pair<Vector2f, int>> Splits;

    PlayerShipComponent* PlayerPSC = nullptr;
    CurrentRegistry.MakeView<PlayerShipComponent>().Each([&](Entity, PlayerShipComponent& PSC) { PlayerPSC = &PSC; });

    for (auto& Bul : Bullets)
    {
        for (auto& Ast : Asteroids)
        {
            if (DeadBullets.count(Bul.E) || DeadAsteroids.count(Ast.E)) continue;

            if ((Bul.Pos - Ast.Pos).Length() < Ast.Radius + BulletRadius)
            {
                DeadBullets.insert(Bul.E);
                DeadAsteroids.insert(Ast.E);

                if (PlayerPSC)
                {
                    int Points = Ast.Tier == 3 ? 20 : (Ast.Tier == 2 ? 50 : 100);
                    PlayerPSC->Score += Points;

                    ScoreChangedPayload ScoreP;
                    ScoreP.NewScore = PlayerPSC->Score;
                    App::Get().GetSignalManager()->Dispatch(Signal_ScoreChanged, ScoreP);
                }

                SpawnExplosion(CurrentRegistry, Ast.Pos, Ast.Tier);

                if (Ast.Tier > 1)
                {
                    Splits.push_back({Ast.Pos, Ast.Tier - 1});
                    Splits.push_back({Ast.Pos, Ast.Tier - 1});
                }
            }
        }
    }

    CurrentRegistry.MakeView<TransformComponent, PlayerShipComponent>().Each(
        [&](Entity, TransformComponent& PTC, PlayerShipComponent& PSC)
        {
            if (PSC.IsDead || PSC.IsInvincible) return;

            for (auto& Ast : Asteroids)
            {
                if (DeadAsteroids.count(Ast.E)) continue;

                if ((PTC.Position - Ast.Pos).Length() < Ast.Radius + ShipRadius)
                {
                    PSC.Lives--;
                    PSC.IsDead       = true;
                    PSC.RespawnTimer = 2.0f;

                    LivesChangedPayload LivesP;
                    LivesP.NewLives = PSC.Lives;
                    App::Get().GetSignalManager()->Dispatch(Signal_LivesChanged, LivesP);

                    SpawnExplosion(CurrentRegistry, PTC.Position, 2);
                    break;
                }
            }
        });

    for (auto E : DeadBullets)   CurrentRegistry.DestroyEntity(E);
    for (auto E : DeadAsteroids) CurrentRegistry.DestroyEntity(E);
    for (auto& [Pos, Tier] : Splits) SpawnChildAsteroid(CurrentRegistry, Pos, Tier);
}
