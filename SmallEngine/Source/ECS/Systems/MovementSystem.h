//
// Created by radov on 19.04.2026.
//


#pragma once
#include "ECS/System.h"


class MovementSystem  : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Update;}
};
