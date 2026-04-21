//
// Created by radov on 21.04.2026.
//


#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"

class SE_API UITextEffectSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override{return SystemPhase::Update;}
};
