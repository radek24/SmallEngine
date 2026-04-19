//
// Created by radov on 19.04.2026.
//


#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"

class SE_API LifetimeSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::PostUpdate;}
};
