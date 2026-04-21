//
// Created by radov on 22.04.2026.
//


#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"
#include "Noise/FastNoiseLite.h"

class SE_API ShakerSystem : public System
{
public:
    ShakerSystem();
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override{return SystemPhase::Update;}
private:
    FastNoiseLite Noise;
};
