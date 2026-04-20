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
        RendererRef->DrawFilledCircle(T.Transform.Position,3,b);
        auto FirstLineEnd = T.Transform.Position+Vector2f(100 * T.Transform.Scale.X,0);
        auto FirstLineEndRotated = FirstLineEnd.GetRotated(T.Transform.Position, T.Transform.Rotation);
        auto SecondLineEnd = FirstLineEnd.GetRotated(T.Transform.Position, T.Transform.Rotation + Rotator(90.0f));
        RendererRef->DrawLine(T.Transform.Position, FirstLineEndRotated,1,r);
        RendererRef->DrawLine(T.Transform.Position,SecondLineEnd ,1,g);
    };
    CurrentRegistry.MakeView<TransformComponent>().Each(Callback);
}