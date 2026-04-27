#pragma once
#include <optional>
#include <random>
#include "Engine/Level.h"
#include "Engine/Rendering/TextureManager.h"

class AsteroidsLevel : public Level
{
public:
    AsteroidsLevel();
    void OnEnter() override;
    void OnUpdate(float DeltaTime) override;

private:
    std::optional<Entity> PlayerEntity;
    std::optional<Entity> ScoreTextEntity;
    std::optional<Entity> LivesTextEntity;
    std::optional<Entity> StatusTextEntity;

    TextureHandle ParticleTexture = INVALID_TEXTURE;

    int   WaveNumber          = 1;
    bool  GameOver            = false;
    float GameOverTimer       = 0.0f;
    bool  WaitingForNextWave  = false;
    float WaveTransitionTimer = 0.0f;
    float StatusTextTimer     = 0.0f;

    std::mt19937 RNG;

    void SpawnWave(int AsteroidCount);
    void SpawnAsteroid(Vector2f Pos, int Tier, Vector2f Vel);
    bool HasAsteroids();
    void SetStatusText(const std::string& Text, float Duration);
    void UpdateHUD();
};