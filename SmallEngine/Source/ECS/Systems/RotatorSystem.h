//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include "ECS/System.h"


class RotatorSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Update;};
};
