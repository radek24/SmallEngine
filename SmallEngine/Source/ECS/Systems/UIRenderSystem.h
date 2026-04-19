//
// Created by radov on 19.04.2026.
//


#pragma once
#include <Engine/Rendering/Renderer.h>

#include "ECS/System.h"
#include "Engine/Rendering/FontManager.h"

/** Renders all UI elements on top of the game window. */
class SE_API UIRenderSystem : public System
{
    FontManager& Fonts;
    Renderer* RendererRef;

    struct CachedText
    {
        SDL_Texture* Texture   = nullptr;
        std::string  LastText;
        int          LastSize  = 0;
        SDL_Color    LastColor = {};
    };
    std::unordered_map<Entity, CachedText> Cache;

public:
    UIRenderSystem(Renderer* InRenderer,FontManager& InFonts)
        : Fonts(InFonts), RendererRef(InRenderer) {}

    ~UIRenderSystem() override ;
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::RenderUI;}
    void OnEntityDestroyed(Entity E) override;
};
