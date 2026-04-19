//
// Created by radov on 19.04.2026.
//


#pragma once
#include "Engine/Core.h"
#include "ECS/System.h"


/** Lets you move any entity using WSAD */
class SE_API SimpleControllerSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Update;}
};
