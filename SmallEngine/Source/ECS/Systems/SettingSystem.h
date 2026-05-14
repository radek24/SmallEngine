//
// Created by radov on 14.05.2026.
//


#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"


/** This system draws setting selectors on screen, dev needs to do everything else, like save etc. */
class SE_API SettingSystem : public System
{
public:
    SettingSystem(Registry& R);

    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Update;}
};
