//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include "ECS/System.h"

//TODO: Check what happens when mouse is over and then we destroy this entity.
/** System used to handle button colliders with mouse. */
class UIButtonSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Update;}
};
