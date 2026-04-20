//
// Created by Radovan Šťastný on 20.04.2026.
//

#include "DebugDrawTransformSystem.h"

#include <ECS/Registry.h>

#include "ECS/Components/TransformComponent.h"

void DebugDrawTransformSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [&](Entity E, TransformComponent &T)
    {
        Color r(1.0f, 0.0f, 0.0f, 1.0f);
        Color g(0.0f, 1.0f, 0.0f, 1.0f);
        Color b(0.0f, 0.0f, 1.0f, 1.0f);
        RendererRef->DrawFilledCircle(T.Position,4,b);
        auto FirstLineEnd = T.Position+Vector2f(50 * T.Scale.X,0);
        auto FirstLineEndRotated = FirstLineEnd.GetRotated(T.Position, T.Rotation);
        auto SecondLineEnd = FirstLineEnd.GetRotated(T.Position, T.Rotation + Rotator(90.0f));
        RendererRef->DrawLine(T.Position, FirstLineEndRotated,1,r);
        RendererRef->DrawLine(T.Position,SecondLineEnd ,1,g);
    };
    CurrentRegistry.MakeView<TransformComponent>().Each(Callback);
}