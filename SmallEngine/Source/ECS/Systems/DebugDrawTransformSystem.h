//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include <Engine/Rendering/Renderer.h>

#include "ECS/System.h"


class DebugDrawTransformSystem : public System
{
public:
    DebugDrawTransformSystem(Renderer *RendererRef) : RendererRef(RendererRef) {};
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::RenderUI;}

    Renderer* RendererRef;
};
