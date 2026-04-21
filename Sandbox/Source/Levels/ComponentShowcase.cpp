//
// Created by radov on 21.04.2026.
//

#include "ComponentShowcase.h"

#include <random>
#include <Engine/App.h>

#include "DemoSelectLevel.h"
#include "../Prefab/BackButtonPrefab.h"
#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/RainbowTextEffectComponent.h"
#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/ShakeComponent.h"
#include "ECS/Components/SimpleKeyboardControllerComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/LifetimeSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/RotatorSystem.h"
#include "ECS/Systems/ShakerSystem.h"
#include "ECS/Systems/SimpleControllerSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"
#include "ECS/Systems/UITextEffectSystem.h"

static void MakeSectionLabel(Registry& R, const std::string& Text, const Vector2f& Position)
{
    auto E = R.CreateEntity();
    R.AddComponent<TransformComponent>(E, TransformComponent{Position});
    R.AddComponent<UITextComponent>(E, UITextComponent{.Text = Text, .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 18, .FontColor = Color(0.6f)});
}

void ComponentShowcase::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.05f));

    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(), *Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(), *Textures);
    CurrentRegistry.AddSystem<RotatorSystem>();
    CurrentRegistry.AddSystem<SimpleControllerSystem>();
    CurrentRegistry.AddSystem<LifetimeSystem>();
    CurrentRegistry.AddSystem<UITextEffectSystem>();
    CurrentRegistry.AddSystem<ShakerSystem>();

    {
        auto E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{Vector2f(20, 15)});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{.Text = "COMPONENT SHOWCASE", .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 28});
        CurrentRegistry.AddComponent<RainbowTextEffectComponent>(E);
    }

    auto BallTexture = Textures->LoadTexture("Resources/Textures/T_Ball.png");

    MakeSectionLabel(CurrentRegistry, "SimpleKeyboardController + Sprite  (WASD)", {20, 70});
    {
        auto E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = {200, 140}, .Scale = {0.4f, 0.4f}});
        CurrentRegistry.AddComponent<SpriteComponent>(E, SpriteComponent{.Texture = Textures->LoadTexture("Resources/Textures/T_Cat.jpg")});
        CurrentRegistry.AddComponent<SimpleKeyboardControllerComponent>(E, SimpleKeyboardControllerComponent{.Speed = 200.0f});
    }

    MakeSectionLabel(CurrentRegistry, "Rotator + Sprite", {20, 230});
    {
        auto E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E,TransformComponent{.Position = {200, 350}, .Scale = {0.3f, 0.3f}});
        CurrentRegistry.AddComponent<SpriteComponent>(E,SpriteComponent{.Texture = Textures->LoadTexture("Resources/Textures/T_Fih.png")});
        CurrentRegistry.AddComponent<RotatorComponent>(E,RotatorComponent{20});
    }

    MakeSectionLabel(CurrentRegistry, "Sprite grid + random Lifetime (100x100)", {20, 430});
    {
        std::mt19937 RNG(std::random_device{}());
        std::uniform_real_distribution<float> LifetimeDist(5.0f, 15.0f);
        std::uniform_real_distribution<float> HueDist(0.0f, 360.0f);

        Prefab Dot;
        Dot.Add<TransformComponent>(TransformComponent{.Scale = {0.01f, 0.01f}});
        Dot.Add<SpriteComponent>(SpriteComponent{.Texture = BallTexture});
        Dot.Add<LifetimeComponent>(LifetimeComponent{});

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 100; ++j) {
                constexpr float StartX = 400.0f;
                constexpr float StartY = 400.0f;
                constexpr float Step   = 2.0f;
                auto E = Dot.Instantiate(CurrentRegistry);
                CurrentRegistry.Get<TransformComponent>(E).Position = {StartX + static_cast<float>(j) * Step, StartY + static_cast<float>(i) * Step};
                CurrentRegistry.Get<SpriteComponent>(E).Tint        = Color::FromHSV(HueDist(RNG), 0.8f, 1.0f);
                CurrentRegistry.Get<LifetimeComponent>(E).RemainingSeconds = LifetimeDist(RNG);
            }
        }
    }

    MakeSectionLabel(CurrentRegistry, "UIText + RainbowTextEffect + Shake", {20, 610});
    {
        auto E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{Vector2f(20, 650)});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{.Text = "Hello, ECS!", .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 30});
        CurrentRegistry.AddComponent<ShakeComponent>(E);
        CurrentRegistry.AddComponent<RainbowTextEffectComponent>(E, RainbowTextEffectComponent{.Speed = 60.0f, .Saturation = 1.0f, .Value = 1.0f});
    }



    BackButtonPrefab::Create<DemoSelectLevel>(CurrentRegistry);
}