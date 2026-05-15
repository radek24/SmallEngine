#include "AsteroidsLevel.h"

#include <cmath>
#include <string>
#include "../AsteroidsSignals.h"

#include <Engine/App.h>
#include <Engine/Input/EventHandler.h>
#include <Engine/Math/Rotator.h>

#include "DemoSelectLevel.h"
#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/ParticleComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Systems/LifetimeSystem.h"
#include "ECS/Systems/ParticleSystem.h"
#include "ECS/Systems/RotatorSystem.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"

#include "../Components/AsteroidComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/PlayerShipComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Systems/AsteroidsCollisionSystem.h"
#include "../Systems/AsteroidsMovementSystem.h"
#include "../Systems/AsteroidsRenderSystem.h"
#include "../Systems/PlayerInputSystem.h"
#include "../Systems/PlayerLifecycleSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "Engine/Signals/SignalManager.h"

static constexpr float WinW = 900.0f;
static constexpr float WinH = 900.0f;


AsteroidsLevel::AsteroidsLevel() : RNG(std::random_device{}()) {}


void AsteroidsLevel::SpawnAsteroid(Vector2f Pos, int Tier, Vector2f Vel)
{
    float Radius = Tier == 3 ? 46.0f : (Tier == 2 ? 26.0f : 14.0f);

    std::uniform_real_distribution<float> SpinDist(-50.0f, 50.0f);

    Entity E = CurrentRegistry.CreateEntity();
    CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{Pos});
    CurrentRegistry.AddComponent<VelocityComponent>(E, VelocityComponent{Vel});
    CurrentRegistry.AddComponent<AsteroidComponent>(E, AsteroidComponent{Tier, Radius});
    CurrentRegistry.AddComponent<RotatorComponent>(E, RotatorComponent{SpinDist(RNG)});
}

void AsteroidsLevel::SpawnWave(int AsteroidCount)
{
    std::uniform_real_distribution<float> AngleDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> SpeedDist(35.0f, 75.0f);
    std::uniform_real_distribution<float> PosDist(0.0f, 1.0f);

    const Vector2f Center{WinW * 0.5f, WinH * 0.5f};

    for (int i = 0; i < AsteroidCount; ++i)
    {
        Vector2f Pos;
        do { Pos = Vector2f(PosDist(RNG) * WinW, PosDist(RNG) * WinH); }
        while ((Pos - Center).Length() < 160.0f);

        Rotator Angle = AngleDist(RNG);
        float   Speed = SpeedDist(RNG);
        SpawnAsteroid(Pos, 3, {cosf(Angle.GetAngleRadians()) * Speed, sinf(Angle.GetAngleRadians()) * Speed});
    }
}

bool AsteroidsLevel::HasAsteroids()
{
    return CurrentRegistry.GetPool<AsteroidComponent>().Size() > 0;
}

void AsteroidsLevel::SetStatusText(const std::string& Text, float Duration)
{
    if (StatusTextEntity.has_value())
    {
        auto& UTC = CurrentRegistry.Get<UITextComponent>(*StatusTextEntity);
        UTC.Text = Text;
        UTC.Visible = true;
    }
    StatusTextTimer = Duration;
}


void AsteroidsLevel::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.0f));

    auto* Renderer = App::Get().GetRenderer();
    auto* Window = App::Get().GetWindow();

    ParticleTexture = Textures->LoadTexture("Resources/Textures/T_FireworkParticle.png");

    CurrentRegistry.AddSystem<PlayerLifecycleSystem>(Vector2f{WinW * 0.5f, WinH * 0.5f});
    CurrentRegistry.AddSystem<PlayerInputSystem>();
    CurrentRegistry.AddSystem<AsteroidsMovementSystem>(Window);
    CurrentRegistry.AddSystem<RotatorSystem>();
    CurrentRegistry.AddSystem<ParticleSystem>(0.0f);
    CurrentRegistry.AddSystem<AsteroidsCollisionSystem>(ParticleTexture);
    CurrentRegistry.AddSystem<LifetimeSystem>();
    CurrentRegistry.AddSystem<SoundSystem>();
    CurrentRegistry.AddSystem<AsteroidsRenderSystem>(Renderer);
    CurrentRegistry.AddSystem<UIRenderSystem>(Renderer, *Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(Renderer,*Textures);

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{
            .Position = {WinW * 0.5f, WinH * 0.5f}
        });
        CurrentRegistry.AddComponent<VelocityComponent>(E, VelocityComponent{});
        CurrentRegistry.AddComponent<PlayerShipComponent>(E, PlayerShipComponent{.Lives = App::Get().GetSettings()->LineValue<int>("Lives")});
        PlayerEntity = E;
    }

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{{20, 20}});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{
            .Text = "SCORE: 0", .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 22
        });
        ScoreTextEntity = E;
    }

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{{20, 50}});
        const std::string LivesText = "LIVES: " + std::to_string(App::Get().GetSettings()->LineValue<int>("Lives"));
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{
            .Text = LivesText, .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 22
        });
        LivesTextEntity = E;
    }

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{{290, 440}});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{
            .Text = "WAVE 1", .FontPath = "Resources/Fonts/PacFont.ttf",
            .FontSize = 36, .Visible = true
        });
        StatusTextEntity = E;
        StatusTextTimer  = 2.0f;
    }

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{{20, 860}});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{
            .Text = "ARROWS / WASD: steer   SPACE: fire   ESC: back",
            .FontPath = "Resources/Fonts/PacFont.ttf",
            .FontSize = 14, .FontColor = Color(0.55f)
        });
    }

    auto& SM = *App::Get().GetSignalManager();

    ScoreSubId = SM.Subscribe(Signal_AsteroidDestroyed, [this](SignalPayload& P)
    {
        if (!PlayerEntity.has_value() || !ScoreTextEntity.has_value()) return;
        auto& PSC = CurrentRegistry.Get<PlayerShipComponent>(*PlayerEntity);
        CurrentRegistry.Get<UITextComponent>(*ScoreTextEntity).Text = "SCORE: " + std::to_string(PSC.Score);
    });

    LivesSubId = SM.Subscribe(Signal_PlayerDamaged, [this](SignalPayload&)
    {
        if (!PlayerEntity.has_value() || !LivesTextEntity.has_value()) return;
        auto& PSC = CurrentRegistry.Get<PlayerShipComponent>(*PlayerEntity);
        CurrentRegistry.Get<UITextComponent>(*LivesTextEntity).Text = "LIVES: " + std::to_string(std::max(PSC.Lives, 0));
    });

    SpawnWave(3 + WaveNumber);
}

void AsteroidsLevel::OnExit()
{
    auto& SM = *App::Get().GetSignalManager();
    SM.Unsubscribe(ScoreSubId);
    SM.Unsubscribe(LivesSubId);
}

void AsteroidsLevel::OnUpdate(float DeltaTime)
{
    Level::OnUpdate(DeltaTime);

    if (!PlayerEntity.has_value()) return;
    auto& PSC = CurrentRegistry.Get<PlayerShipComponent>(*PlayerEntity);

    if (EventHandler::IsKeyPressed(SDLK_ESCAPE))
    {
        App::Get().QueueLevelTransition<DemoSelectLevel>();
        return;
    }

    if (StatusTextTimer > 0.0f)
    {
        StatusTextTimer -= DeltaTime;
        if (StatusTextTimer <= 0.0f && StatusTextEntity.has_value())
            CurrentRegistry.Get<UITextComponent>(*StatusTextEntity).Visible = false;
    }

    if (GameOver)
    {
        GameOverTimer -= DeltaTime;
        if (GameOverTimer <= 0.0f)
            App::Get().QueueLevelTransition<DemoSelectLevel>();
        return;
    }

    if (PSC.Lives <= 0 && PSC.IsDead)
    {
        GameOver      = true;
        GameOverTimer = 3.5f;
        SetStatusText("GAME OVER", 999.0f);
    }

    if (!WaitingForNextWave && !HasAsteroids())
    {
        WaitingForNextWave  = true;
        WaveTransitionTimer = 2.5f;
        WaveNumber++;
        SetStatusText("WAVE " + std::to_string(WaveNumber), 2.5f);
    }
    if (WaitingForNextWave)
    {
        WaveTransitionTimer -= DeltaTime;
        if (WaveTransitionTimer <= 0.0f)
        {
            WaitingForNextWave = false;
            SpawnWave(3 + WaveNumber);
        }
    }

}