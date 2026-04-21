//
// Created by radov on 21.04.2026.
//


#pragma once
#include <Engine/Rendering/Renderer.h>

#include "ECS/System.h"


class DebugStatsSystem : public System
{
public:
    DebugStatsSystem(Renderer* RendererRef) : RendererRef(RendererRef){}
    Renderer* RendererRef;
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override{return SystemPhase::RenderUI;}
    bool ShowSystemTimings = false;
};
