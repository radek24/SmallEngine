//
// Created by radov on 20.04.2026.
//

#include "MainMenuLevel.h"

#include <random>
#include <Engine/App.h>

#include "CreditsLevel.h"
#include "../Components/BouncyBallComponent.h"
#include "../Systems/BouncyBallSystem.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"

void MainMenuLevel::OnEnter() {
    App::Get().GetRenderer()->SetClearColor(Color(1.0f));

    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<BouncyBallSystem>(App::Get().GetWindow());
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(),*Textures);
    auto OnHoverCall   = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.0f); };
    auto OnUnhoverCall = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f); };
    Prefab ClickableButton;
    ClickableButton.Add<TransformComponent>({{20.0f, 50.0f},{1.0f, 1.0f},{0.0f}});
    ClickableButton.Add<UITextComponent>({.FontPath = "Resources/Fonts/PacFont.ttf",.FontSize = 25,.FontColor = Color(0.5f)});
    ClickableButton.Add<UIButtonComponent>({.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {200,30}});


    Entity PlayGameButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.GetPool<TransformComponent>().Get(PlayGameButton).Position += Vector2f(0,40);
    CurrentRegistry.GetPool<UITextComponent>().Get(PlayGameButton).Text = "Demos";

    auto OnClickCredits = [this] (Entity self) {App::Get().QueueLevelTransition<CreditsLevel>();};
    Entity CreditsButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.GetPool<TransformComponent>().Get(CreditsButton).Position += Vector2f(0,80);
    CurrentRegistry.GetPool<UITextComponent>().Get(CreditsButton).Text = "Credits";
    CurrentRegistry.GetPool<UIButtonComponent>().Get(CreditsButton).OnMouseUp = OnClickCredits;

    Entity SettingsButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.GetPool<TransformComponent>().Get(SettingsButton).Position += Vector2f(0,120);
    CurrentRegistry.GetPool<UITextComponent>().Get(SettingsButton).Text = "Settings";

    auto OnClickExit = [this] (Entity self) {App::Get().Stop();};
    Entity ExitGameButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.GetPool<TransformComponent>().Get(ExitGameButton).Position += Vector2f(0,160);
    CurrentRegistry.GetPool<UITextComponent>().Get(ExitGameButton).Text = "Exit";
    CurrentRegistry.GetPool<UIButtonComponent>().Get(ExitGameButton).OnMouseUp = OnClickExit;

    Prefab BouncyBall;
    BouncyBall.Add<TransformComponent>({{300.0f, 300.0f},{0.5f},{0.0f}});
    BouncyBall.Add<BouncyBallComponent>({128,{100,100}});
    BouncyBall.Add<SpriteComponent>({.Texture = Textures->LoadTexture("Resources/Textures/T_Ball.png")});

    std::mt19937 RNG(std::random_device{}());
    std::uniform_real_distribution<float> VelocityDist(-1000, 1000);
    std::uniform_real_distribution<float> SizeDist(0.01, 0.3);
    std::uniform_real_distribution<float> DampingDist(0.5, 0.9);
    std::uniform_real_distribution<float> HueDist(0, 360);
    for (int i = 0; i < 1000; ++i)
    {
        auto Ball = BouncyBall.Instantiate(CurrentRegistry);
        CurrentRegistry.GetPool<BouncyBallComponent>().Get(Ball).Velocity = Vector2f(VelocityDist(RNG),VelocityDist(RNG));
        CurrentRegistry.GetPool<BouncyBallComponent>().Get(Ball).Damping = DampingDist(RNG);
        CurrentRegistry.GetPool<TransformComponent>().Get(Ball).Scale = Vector2f(SizeDist(RNG));
        CurrentRegistry.GetPool<SpriteComponent>().Get(Ball).Tint = Color::FromHSV(HueDist(RNG),0.2,1.0);
    }
    Level::OnEnter();
}
