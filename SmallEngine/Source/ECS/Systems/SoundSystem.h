//
// Created by radov on 22.04.2026.
//


#pragma once
#include "ECS/System.h"
#include "Engine/SoundManager.h"


class SE_API SoundSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::PostUpdate;}
};
