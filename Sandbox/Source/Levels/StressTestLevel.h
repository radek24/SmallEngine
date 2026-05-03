//
// Created by radov on 30.04.2026.
//

#pragma once
#include <optional>
#include "Engine/Level.h"

struct StressEntityTag {};

class StressTestLevel : public Level
{
public:
    void OnEnter() override;
    void OnUpdate(float DeltaTime) override;

private:
    void SpawnEntities(int Count);
    void ClearEntities();

    int TargetCount = 1000;
    TextureHandle BallTexture = INVALID_TEXTURE;
    float SmoothedFps = 60.0f;

    std::optional<Entity> FpsLabel;
    std::optional<Entity> AliveLabel;
    std::optional<Entity> TargetLabel;
};