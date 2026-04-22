//
// Created by radov on 20.04.2026.
//

#include "MainMenuLevel.h"

#include <random>
#include <Engine/App.h>

#include "CreditsLevel.h"
#include "DemoSelectLevel.h"
#include "../Components/BouncyBallComponent.h"
#include "../Systems/BouncyBallSystem.h"
#include "ECS/Components/PlaySoundRequestComponent.h"
#include "ECS/Components/RainbowTextEffectComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"
#include "ECS/Systems/UITextEffectSystem.h"

void MainMenuLevel::OnEnter() {
    App::Get().GetRenderer()->SetClearColor(Color(1.0f));

    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<BouncyBallSystem>(App::Get().GetWindow());
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(),*Textures);
    CurrentRegistry.AddSystem<UITextEffectSystem>();
    CurrentRegistry.AddSystem<SoundSystem>();

    auto OnHoverCall   = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.0f); CurrentRegistry.AddComponent<PlaySoundRequestComponent>(self).SoundPath = "Resources/Sounds/S_ButtonHover.mp3"; };
    auto OnUnhoverCall = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f); };
    Prefab ClickableButton;
    ClickableButton.Add<TransformComponent>({{20.0f, 50.0f},{1.0f, 1.0f},{0.0f}});
    ClickableButton.Add<UITextComponent>({.FontPath = "Resources/Fonts/PacFont.ttf",.FontSize = 25,.FontColor = Color(0.5f)});
    ClickableButton.Add<UIButtonComponent>({.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {200,30}});

    Entity GameTitle = CurrentRegistry.CreateEntity();
    CurrentRegistry.AddComponent<TransformComponent>(GameTitle,TransformComponent{Vector2f(20,20)});
    CurrentRegistry.AddComponent<UITextComponent>(GameTitle,UITextComponent{"ECS ENGINE SHOWCASE", "Resources/Fonts/PacFont.ttf",35});
    CurrentRegistry.AddComponent<RainbowTextEffectComponent>(GameTitle);

    auto OnClickDemo = [this] (Entity self) {App::Get().QueueLevelTransition<DemoSelectLevel>();};
    Entity PlayGameButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(PlayGameButton).Position += Vector2f(0,40);
    CurrentRegistry.Get<UITextComponent>(PlayGameButton).Text = "Demos";
    CurrentRegistry.Get<UIButtonComponent>(PlayGameButton).OnMouseUp = OnClickDemo;

    auto OnClickCredits = [this] (Entity self) {App::Get().QueueLevelTransition<CreditsLevel>();};
    Entity CreditsButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(CreditsButton).Position += Vector2f(0,80);
    CurrentRegistry.Get<UITextComponent>(CreditsButton).Text = "Credits";
    CurrentRegistry.Get<UIButtonComponent>(CreditsButton).OnMouseUp = OnClickCredits;

    Entity SettingsButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(SettingsButton).Position += Vector2f(0,120);
    CurrentRegistry.Get<UITextComponent>(SettingsButton).Text = "Settings";

    auto OnClickExit = [this] (Entity self) {App::Get().Stop();};
    Entity ExitGameButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(ExitGameButton).Position += Vector2f(0,160);
    CurrentRegistry.Get<UITextComponent>(ExitGameButton).Text = "Exit";
    CurrentRegistry.Get<UIButtonComponent>(ExitGameButton).OnMouseUp = OnClickExit;

    Prefab BouncyBall;
    BouncyBall.Add<TransformComponent>({{300.0f, 300.0f},{0.5f},{0.0f}});
    BouncyBall.Add<BouncyBallComponent>({128,{100,100}});
    BouncyBall.Add<SpriteComponent>({.Texture = Textures->LoadTexture("Resources/Textures/T_Ball.png")});

    std::mt19937 RNG(std::random_device{}());
    std::uniform_real_distribution<float> VelocityDist(-1000, 1000);
    std::uniform_real_distribution<float> SizeDist(0.01, 0.3);
    std::uniform_real_distribution<float> DampingDist(0.5, 0.9);
    std::uniform_real_distribution<float> HueDist(0, 360);
    for (int i = 0; i < 10000; ++i)
    {
        auto Ball = BouncyBall.Instantiate(CurrentRegistry);
        CurrentRegistry.Get<BouncyBallComponent>(Ball).Velocity = Vector2f(VelocityDist(RNG),VelocityDist(RNG));
        CurrentRegistry.Get<BouncyBallComponent>(Ball).Damping = DampingDist(RNG);
        CurrentRegistry.Get<TransformComponent>(Ball).Scale = Vector2f(SizeDist(RNG));
        CurrentRegistry.Get<SpriteComponent>(Ball).Tint = Color::FromHSV(HueDist(RNG),0.2,1.0);
    }
    Level::OnEnter();
}
