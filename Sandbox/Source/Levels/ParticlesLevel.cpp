//
// Created by radov on 22.04.2026.
//

#include "ParticlesLevel.h"

#include <random>
#include <Engine/App.h>
#include <Engine/EventHandler.h>
#include <Engine/Math/MathUtils.h>

#include "DemoSelectLevel.h"
#include "../Prefab/BackButtonPrefab.h"
#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/ParticleComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Systems/LifetimeSystem.h"
#include "ECS/Systems/ParticleSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"

static constexpr int ParticlesPerBurst = 80;
static constexpr float MinSpeed = 80.0f;
static constexpr float MaxSpeed = 400.0f;
static constexpr float MinLifetime = 0.8f;
static constexpr float MaxLifetime = 2.2f;
static constexpr float ParticleScale = 0.08f;

void ParticlesLevel::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.05f));

    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(), *Textures);
    CurrentRegistry.AddSystem<ParticleSystem>(300.0f);
    CurrentRegistry.AddSystem<LifetimeSystem>();
    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(), *Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<SoundSystem>();

    ParticleTexture = Textures->LoadTexture("Resources/Textures/T_FireworkParticle.png");

    static constexpr size_t MaxLiveParticles = ParticlesPerBurst * 10;
    CurrentRegistry.ReserveEntities(MaxLiveParticles);
    CurrentRegistry.GetPool<TransformComponent>().Reserve(MaxLiveParticles);
    CurrentRegistry.GetPool<SpriteComponent>().Reserve(MaxLiveParticles);
    CurrentRegistry.GetPool<ParticleComponent>().Reserve(MaxLiveParticles);
    CurrentRegistry.GetPool<LifetimeComponent>().Reserve(MaxLiveParticles);

    BackButtonPrefab::Create<DemoSelectLevel>(CurrentRegistry);
}

void ParticlesLevel::OnUpdate(float DeltaTime)
{
    Level::OnUpdate(DeltaTime);

    if (EventHandler::IsMouseButtonPressed(MouseButton::Left))
        SpawnFirework(EventHandler::GetMousePos());
}

void ParticlesLevel::SpawnFirework(const Vector2f& Position)
{
    static std::mt19937 RNG(std::random_device{}());
    std::uniform_real_distribution<float> SpeedDist(MinSpeed, MaxSpeed);
    std::uniform_real_distribution<float> AngleDist(0.0f, 2.0f * MathUtils::PI);
    std::uniform_real_distribution<float> LifetimeDist(MinLifetime, MaxLifetime);
    std::uniform_real_distribution<float> HueDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> ScaleDist(ParticleScale * 0.5f, ParticleScale * 1.5f);

    float Hue = HueDist(RNG);

    for (int i = 0; i < ParticlesPerBurst; ++i)
    {
        float Angle = AngleDist(RNG);
        float Speed = SpeedDist(RNG);

        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = Position,.Scale = Vector2f(ScaleDist(RNG))});
        CurrentRegistry.AddComponent<SpriteComponent>(E, SpriteComponent{.Texture = ParticleTexture,.Tint = Color::FromHSV(Hue + AngleDist(RNG) * 20.0f, 0.9f, 1.0f)});
        CurrentRegistry.AddComponent<ParticleComponent>(E, ParticleComponent{
            .Velocity     = Vector2f(cosf(Angle) * Speed, sinf(Angle) * Speed),
            .Damping      = 0.92f,
            .GravityScale = 1.0f
        });
        CurrentRegistry.AddComponent<LifetimeComponent>(E, LifetimeComponent{.RemainingSeconds = LifetimeDist(RNG)});
    }
}