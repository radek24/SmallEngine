#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"
#include "Engine/Math/Rotator.h"
#include "Engine/Rendering/Renderer.h"
#include "Engine/Math/Color.h"

class AsteroidsRenderSystem : public System
{
public:
    explicit AsteroidsRenderSystem(Renderer* RendererRef) : RendererRef(RendererRef) {}
    void Update(Registry& CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::Render; }

private:
    Renderer* RendererRef;

    void DrawPolygon(const Vector2f &Center, float Radius, int Sides, Rotator Rot, Color C) const;
    void DrawShip(const Vector2f &Center, Rotator Rot, Color C) const;
};
