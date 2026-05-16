#include "AsteroidsLevel.h"

#include <string>

#include <Engine/App.h>

#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Systems/LifetimeSystem.h"
#include "ECS/Systems/ParticleSystem.h"
#include "ECS/Systems/RotatorSystem.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"
#include "ECS/Systems/RenderSystem.h"

#include "../AsteroidsSignals.h"
#include "../Components/AsteroidsGameTags.h"
#include "../Components/PlayerShipComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Systems/AsteroidsCollisionSystem.h"
#include "../Systems/AsteroidsGameSystem.h"
#include "../Systems/AsteroidsMovementSystem.h"
#include "../Systems/AsteroidsRenderSystem.h"
#include "../Systems/AsteroidsSoundSystem.h"
#include "../Systems/PlayerInputSystem.h"
#include "../Systems/PlayerLifecycleSystem.h"

static constexpr float WinW = 900.0f;
static constexpr float WinH = 900.0f;

void AsteroidsLevel::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.0f));

    auto* Renderer = App::Get().GetRenderer();
    auto* Window   = App::Get().GetWindow();

    ParticleTexture = Textures->LoadTexture("Resources/Textures/T_FireworkParticle.png");

    CurrentRegistry.AddSystem<PlayerLifecycleSystem>(Vector2f{WinW * 0.5f, WinH * 0.5f});
    CurrentRegistry.AddSystem<PlayerInputSystem>();
    CurrentRegistry.AddSystem<AsteroidsMovementSystem>(Window);
    CurrentRegistry.AddSystem<RotatorSystem>();
    CurrentRegistry.AddSystem<ParticleSystem>(0.0f);
    CurrentRegistry.AddSystem<AsteroidsCollisionSystem>(ParticleTexture);
    CurrentRegistry.AddSystem<LifetimeSystem>();
    CurrentRegistry.AddSystem<AsteroidsSoundSystem>();
    CurrentRegistry.AddSystem<AsteroidsGameSystem>(Window);
    CurrentRegistry.AddSystem<AsteroidsRenderSystem>(Renderer);
    CurrentRegistry.AddSystem<UIRenderSystem>(Renderer, *Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(Renderer, *Textures);

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = {WinW * 0.5f, WinH * 0.5f}});
        CurrentRegistry.AddComponent<VelocityComponent>(E, VelocityComponent{});
        CurrentRegistry.AddComponent<PlayerShipComponent>(E, PlayerShipComponent{.Lives = App::Get().GetSettings()->LineValue<int>("Lives")});
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
        CurrentRegistry.AddComponent<StatusTextTag>(E, StatusTextTag{2.0f});
    }

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{{20, 860}});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{
            .Text      = "ARROWS / WASD: steer   SPACE: fire   ESC: back",
            .FontPath  = "Resources/Fonts/PacFont.ttf",
            .FontSize  = 14,
            .FontColor = Color(0.55f)
        });
    }

    auto& SM = *App::Get().GetSignalManager();

    ScoreSubId = SM.Subscribe(Signal_ScoreChanged, [this](SignalPayload& P)
    {
        if (!ScoreTextEntity.has_value()) return;
        auto& Payload = static_cast<ScoreChangedPayload&>(P);
        CurrentRegistry.Get<UITextComponent>(*ScoreTextEntity).Text = "SCORE: " + std::to_string(Payload.NewScore);
    });

    LivesSubId = SM.Subscribe(Signal_LivesChanged, [this](SignalPayload& P)
    {
        if (!LivesTextEntity.has_value()) return;
        auto& Payload = static_cast<LivesChangedPayload&>(P);
        CurrentRegistry.Get<UITextComponent>(*LivesTextEntity).Text = "LIVES: " + std::to_string(std::max(Payload.NewLives, 0));
    });
}

void AsteroidsLevel::OnExit()
{
    auto& SM = *App::Get().GetSignalManager();
    SM.Unsubscribe(ScoreSubId);
    SM.Unsubscribe(LivesSubId);
}
