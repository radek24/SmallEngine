//
// Created by radov on 22.04.2026.
//

#include "ShakerSystem.h"

#include <ECS/Registry.h>
#include <Engine/App.h>

#include "ECS/Components/ShakeComponent.h"
#include "ECS/Components/TransformComponent.h"

ShakerSystem::ShakerSystem()
{
    Noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
}

void ShakerSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [DeltaTime, this](Entity E,ShakeComponent &S,TransformComponent &T)
    {
        T.Position.X += Noise.GetNoise(S.Time,0.0f) * S.Amplitude;
        T.Position.Y += Noise.GetNoise(0.0f,S.Time) * S.Amplitude;
        S.Time += DeltaTime * S.Frequency;
    };
    CurrentRegistry.MakeView<ShakeComponent,TransformComponent>().Each(Callback);
}
