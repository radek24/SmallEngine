#include "AsteroidsGameSystem.h"

#include <cmath>
#include <string>

#include <ECS/Registry.h>
#include <Engine/App.h>
#include <Engine/Input/EventHandler.h>
#include <Engine/Math/Rotator.h>

#include "../Levels/DemoSelectLevel.h"
#include "../AsteroidsSignals.h"
#include "../Components/AsteroidComponent.h"
#include "../Components/AsteroidsGameTags.h"
#include "../Components/PlayerShipComponent.h"
#include "../Components/VelocityComponent.h"
#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"

AsteroidsGameSystem::AsteroidsGameSystem(Window* Win)
    : CurrentWindow(Win), RNG(std::random_device{}())
{}

bool AsteroidsGameSystem::HasAsteroids(Registry& R)
{
    return R.GetPool<AsteroidComponent>().Size() > 0;
}

void AsteroidsGameSystem::SetStatusText(Registry& R, const std::string& Text, float Duration)
{
    R.MakeView<UITextComponent, StatusTextTag>().Each(
        [&](Entity, UITextComponent& UTC, StatusTextTag& STT)
        {
            UTC.Text    = Text;
            UTC.Visible = true;
            STT.Timer   = Duration;
        });
}

void AsteroidsGameSystem::SpawnAsteroid(Registry& R, Vector2f Pos, int Tier, Vector2f Vel)
{
    std::uniform_real_distribution<float> SpinDist(-50.0f, 50.0f);
    Entity E = R.CreateEntity();
    R.AddComponent<TransformComponent>(E, TransformComponent{Pos});
    R.AddComponent<VelocityComponent>(E, VelocityComponent{Vel});
    R.AddComponent<AsteroidComponent>(E, AsteroidComponent::FromTier(Tier));
    R.AddComponent<RotatorComponent>(E, RotatorComponent{SpinDist(RNG)});
}

void AsteroidsGameSystem::SpawnWave(Registry& R, int Count)
{
    const float W = static_cast<float>(CurrentWindow->GetLogicalWidth());
    const float H = static_cast<float>(CurrentWindow->GetLogicalHeight());
    const Vector2f Center{W * 0.5f, H * 0.5f};

    std::uniform_real_distribution<float> AngleDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> SpeedDist(35.0f, 75.0f);
    std::uniform_real_distribution<float> PosX(0.0f, W);
    std::uniform_real_distribution<float> PosY(0.0f, H);

    for (int i = 0; i < Count; ++i)
    {
        Vector2f Pos;
        do { Pos = Vector2f(PosX(RNG), PosY(RNG)); }
        while ((Pos - Center).Length() < 160.0f);

        Rotator Angle = AngleDist(RNG);
        float   Speed = SpeedDist(RNG);
        SpawnAsteroid(R, Pos, 3, {cosf(Angle.GetAngleRadians()) * Speed, sinf(Angle.GetAngleRadians()) * Speed});
    }
}

void AsteroidsGameSystem::Update(Registry& R, float DeltaTime)
{
    if (!bInitialized)
    {
        bInitialized = true;
        SpawnWave(R, 3 + WaveNumber);
        return;
    }

    if (EventHandler::IsKeyPressed(SDLK_ESCAPE))
    {
        App::Get().QueueLevelTransition<DemoSelectLevel>();
        return;
    }

    R.MakeView<UITextComponent, StatusTextTag>().Each(
        [&](Entity, UITextComponent& UTC, StatusTextTag& STT)
        {
            if (STT.Timer > 0.0f)
            {
                STT.Timer -= DeltaTime;
                if (STT.Timer <= 0.0f)
                    UTC.Visible = false;
            }
        });

    if (GameOver)
    {
        GameOverTimer -= DeltaTime;
        if (GameOverTimer <= 0.0f)
            App::Get().QueueLevelTransition<DemoSelectLevel>();
        return;
    }

    R.MakeView<PlayerShipComponent>().Each(
        [&](Entity, PlayerShipComponent& PSC)
        {
            if (PSC.Lives <= 0 && PSC.IsDead)
            {
                GameOver      = true;
                GameOverTimer = 3.5f;
                SetStatusText(R, "GAME OVER", 999.0f);
            }
        });

    if (GameOver) return;

    if (!WaitingForNextWave && !HasAsteroids(R))
    {
        WaitingForNextWave  = true;
        WaveTransitionTimer = 2.5f;
        WaveNumber++;
        SetStatusText(R, "WAVE " + std::to_string(WaveNumber), 2.5f);
        App::Get().GetSignalManager()->Dispatch(Signal_WaveCleared, SignalPayload::GetEmpty());
    }
    if (WaitingForNextWave)
    {
        WaveTransitionTimer -= DeltaTime;
        if (WaveTransitionTimer <= 0.0f)
        {
            WaitingForNextWave = false;
            SpawnWave(R, 3 + WaveNumber);
        }
    }
}
