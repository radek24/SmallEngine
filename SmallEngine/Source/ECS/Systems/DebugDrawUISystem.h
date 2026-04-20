//
// Created by radov on 20.04.2026.
//


#pragma once
#include <Engine/Rendering/Renderer.h>

#include "ECS/System.h"


class DebugDrawUISystem : public System
{
public:
    DebugDrawUISystem(Renderer *RendererRef) : RendererRef(RendererRef) {};
    Renderer* RendererRef;

    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::RenderUI;}
};
