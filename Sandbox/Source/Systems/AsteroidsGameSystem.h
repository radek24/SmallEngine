#pragma once
#include <random>
#include "ECS/System.h"
#include "Engine/Core.h"
#include "Engine/Rendering/Window.h"

class AsteroidsGameSystem : public System
{
public:
    explicit AsteroidsGameSystem(Window* Win);

    void Update(Registry& R, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::Update; }

private:
    Window*     CurrentWindow;
    int         WaveNumber          = 1;
    bool        bInitialized        = false;
    bool        WaitingForNextWave  = false;
    float       WaveTransitionTimer = 0.0f;
    bool        GameOver            = false;
    float       GameOverTimer       = 0.0f;
    std::mt19937 RNG;

    static bool HasAsteroids(Registry& R);
    void SetStatusText(Registry& R, const std::string& Text, float Duration);
    void SpawnAsteroid(Registry& R, Vector2f Pos, int Tier, Vector2f Vel);
    void SpawnWave(Registry& R, int Count);
};
