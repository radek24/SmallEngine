//
// Created by radov on 19.04.2026.
//


#pragma once
#include <Engine/Rendering/Renderer.h>

#include "ECS/System.h"
#include "Engine/Rendering/TextureManager.h"


/** Generic render system used for rendering sprites and more. Supports Z-Sorting*/
class SE_API RenderSystem : public System
{
public:
    RenderSystem(Renderer* RendererRef, TextureManager& Textures) :RendererRef(RendererRef),Textures(Textures){};
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Render;}
private:
    Renderer* RendererRef;
    TextureManager& Textures;
};
