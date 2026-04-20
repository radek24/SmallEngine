//
// Created by radov on 19.04.2026.
//


#pragma once
#include <Engine/Rendering/Renderer.h>

#include "ECS/System.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "Engine/Rendering/TextureManager.h"

struct DrawCall
{
    SpriteComponent* SC;
    TransformComponent* TC;
    int ZOrder;
    Entity::IdType EntityID;
};

/** Generic render system used for rendering sprites and more. Supports Z-Sorting*/
class SE_API RenderSystem : public System
{
public:
    RenderSystem(Renderer* RendererRef, TextureManager& Textures);
    void Update(Registry &CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Render;}
private:
    Renderer* RendererRef;
    TextureManager& Textures;
    std::vector<DrawCall> Queue;

};
