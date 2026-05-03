//
// Created by radov on 30.04.2026.
//

#include "StressTestLevel.h"

#include <random>
#include <string>
#include <vector>
#include <Engine/App.h>

#include "DemoSelectLevel.h"
#include "../Prefab/BackButtonPrefab.h"
#include "../Components/BouncyBallComponent.h"
#include "../Systems/BouncyBallSystem.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"

static constexpr int MinCount = 0;
static constexpr int MaxCount = 500000;
static constexpr int InitialReserve = 5000;
static const char* FontPath = "Resources/Fonts/PacFont.ttf";

void StressTestLevel::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.08f));

    CurrentRegistry.AddSystem<BouncyBallSystem>(App::Get().GetWindow());
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(), *Textures);
    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(), *Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<SoundSystem>();

    BallTexture = Textures->LoadTexture("Resources/Textures/T_Ball.png");

    CurrentRegistry.ReserveEntities(InitialReserve + 50);
    CurrentRegistry.GetPool<StressEntityTag>().Reserve(InitialReserve);
    CurrentRegistry.GetPool<TransformComponent>().Reserve(InitialReserve + 50);
    CurrentRegistry.GetPool<SpriteComponent>().Reserve(InitialReserve + 50);
    CurrentRegistry.GetPool<BouncyBallComponent>().Reserve(InitialReserve);

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = {20, 20}});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{.Text = "ENTITY STRESS TEST", .FontPath = FontPath, .FontSize = 28, .FontColor = Color(1)});
    }

    {
        FpsLabel = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(*FpsLabel, TransformComponent{.Position = {560, 20}});
        CurrentRegistry.AddComponent<UITextComponent>(*FpsLabel, UITextComponent{.Text = "FPS: --", .FontPath = FontPath, .FontSize = 22, .FontColor = Color(0.4f, 1.0f, 0.4f)});

        AliveLabel = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(*AliveLabel, TransformComponent{.Position = {560, 55}});
        CurrentRegistry.AddComponent<UITextComponent>(*AliveLabel, UITextComponent{.Text = "Alive: 0", .FontPath = FontPath, .FontSize = 22, .FontColor = Color(0.4f, 1.0f, 0.4f)});
    }

    {
        Entity Label = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(Label, TransformComponent{.Position = {20, 110}});
        CurrentRegistry.AddComponent<UITextComponent>(Label, UITextComponent{.Text = "Spawn Count:", .FontPath = FontPath, .FontSize = 20, .FontColor = Color(0.8f)});

        TargetLabel = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(*TargetLabel, TransformComponent{.Position = {20, 145}});
        CurrentRegistry.AddComponent<UITextComponent>(*TargetLabel, UITextComponent{.Text = "1000", .FontPath = FontPath, .FontSize = 28, .FontColor = Color(1, 1, 0)});
    }

    auto MakeCountButton = [&](const char* Label, Vector2f Pos, int Delta)
    {
        auto OnHover = [this](Entity self){ CurrentRegistry.Get<UITextComponent>(self).FontColor = Color(1, 0.8f, 0); };
        auto OnUnhover = [this](Entity self){ CurrentRegistry.Get<UITextComponent>(self).FontColor = Color(1); };
        auto OnClick = [this, Delta](Entity self)
        {
            TargetCount = std::max(MinCount, std::min(MaxCount, TargetCount + Delta));
            CurrentRegistry.Get<UITextComponent>(*TargetLabel).Text = std::to_string(TargetCount);
        };
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = Pos});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{.Text = Label, .FontPath = FontPath, .FontSize = 20, .FontColor = Color(1)});
        CurrentRegistry.AddComponent<UIButtonComponent>(E, UIButtonComponent{.OnMouseUp = OnClick, .OnHover = OnHover, .OnUnhover = OnUnhover, .Size = {100, 30}});
    };

    MakeCountButton("-1000", {20,  195}, -1000);
    MakeCountButton("-100",  {130, 195}, -100);
    MakeCountButton("-10",   {230, 195}, -10);
    MakeCountButton("+10",   {310, 195}, +10);
    MakeCountButton("+100",  {390, 195}, +100);
    MakeCountButton("+1000", {490, 195}, +1000);


    auto MakeActionButton = [&](const char* Label, Vector2f Pos, std::function<void(Entity)> Action)
    {
        auto OnHover   = [this](Entity self){ CurrentRegistry.Get<UITextComponent>(self).FontColor = Color(0.5f); };
        auto OnUnhover = [this](Entity self){ CurrentRegistry.Get<UITextComponent>(self).FontColor = Color(1); };
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = Pos});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{.Text = Label, .FontPath = FontPath, .FontSize = 25, .FontColor = Color(1)});
        CurrentRegistry.AddComponent<UIButtonComponent>(E, UIButtonComponent{.OnMouseUp = Action, .OnHover = OnHover, .OnUnhover = OnUnhover, .Size = {160, 35}});
    };

    MakeActionButton("SPAWN", {20,  250}, [this](Entity){ SpawnEntities(TargetCount); });
    MakeActionButton("CLEAR", {210, 250}, [this](Entity){ ClearEntities(); });

    {
        Entity E = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{.Position = {20, 310}});
        CurrentRegistry.AddComponent<UITextComponent>(E, UITextComponent{.Text = "LMB: repel   RMB: attract", .FontPath = FontPath, .FontSize = 18, .FontColor = Color(0.55f)});
    }

    BackButtonPrefab::Create<DemoSelectLevel>(CurrentRegistry);
}

void StressTestLevel::OnUpdate(float DeltaTime)
{
    Level::OnUpdate(DeltaTime);

    constexpr float Alpha = 0.05f;
    SmoothedFps = SmoothedFps * (1.0f - Alpha) + (1.0f / DeltaTime) * Alpha;

    int Alive = static_cast<int>(CurrentRegistry.GetPool<StressEntityTag>().Size());
    CurrentRegistry.Get<UITextComponent>(*FpsLabel).Text  = "FPS: " + std::to_string(static_cast<int>(SmoothedFps));
    CurrentRegistry.Get<UITextComponent>(*AliveLabel).Text = "Alive: " + std::to_string(Alive);
}

void StressTestLevel::SpawnEntities(int Count)
{
    if (Count <= 0) return;

    static std::mt19937 RNG(std::random_device{}());
    const float WinW = static_cast<float>(App::Get().GetWindow()->GetWidth());
    const float WinH = static_cast<float>(App::Get().GetWindow()->GetHeight());
    std::uniform_real_distribution<float> PosXDist(50, WinW - 50);
    std::uniform_real_distribution<float> PosYDist(50, WinH / 2.0f);
    std::uniform_real_distribution<float> VelDist(-600, 600);
    std::uniform_real_distribution<float> ScaleDist(0.02f, 0.10f);
    std::uniform_real_distribution<float> HueDist(0, 360);
    std::uniform_real_distribution<float> DampingDist(0.7f, 0.95f);

    int CurrentAlive = static_cast<int>(CurrentRegistry.GetPool<StressEntityTag>().Size());
    int ActualCount = std::min(Count, MaxCount - CurrentAlive);
    if (ActualCount <= 0) return;

    CurrentRegistry.ReserveEntities(CurrentAlive + ActualCount + 50);
    CurrentRegistry.GetPool<StressEntityTag>().Reserve(CurrentAlive + ActualCount);
    CurrentRegistry.GetPool<TransformComponent>().Reserve(CurrentAlive + ActualCount + 50);
    CurrentRegistry.GetPool<SpriteComponent>().Reserve(CurrentAlive + ActualCount + 50);
    CurrentRegistry.GetPool<BouncyBallComponent>().Reserve(CurrentAlive + ActualCount);

    for (int i = 0; i < ActualCount; ++i)
    {
        Entity E = CurrentRegistry.CreateEntity();
        float Scale = ScaleDist(RNG);
        CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{
            .Position = {PosXDist(RNG), PosYDist(RNG)},
            .Scale    = Vector2f(Scale)
        });
        CurrentRegistry.AddComponent<SpriteComponent>(E, SpriteComponent{
            .Texture = BallTexture,
            .Tint    = Color::FromHSV(HueDist(RNG), 0.8f, 1.0f)
        });
        CurrentRegistry.AddComponent<BouncyBallComponent>(E, BouncyBallComponent{
            .Size     = 128.0f,
            .Velocity = Vector2f(VelDist(RNG), VelDist(RNG)),
            .Damping  = DampingDist(RNG)
        });
        CurrentRegistry.AddComponent<StressEntityTag>(E, StressEntityTag{});
    }
}

void StressTestLevel::ClearEntities()
{
    std::vector<Entity> ToDestroy;
    ToDestroy.reserve(CurrentRegistry.GetPool<StressEntityTag>().Size());
    CurrentRegistry.MakeView<StressEntityTag>().Each([&ToDestroy](Entity E, StressEntityTag&)
    {
        ToDestroy.push_back(E);
    });
    for (Entity E : ToDestroy)
        CurrentRegistry.DestroyEntity(E);
}