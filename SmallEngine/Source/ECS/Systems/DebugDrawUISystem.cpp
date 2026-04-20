//
// Created by radov on 20.04.2026.
//

#include "DebugDrawUISystem.h"

#include <ECS/Registry.h>
#include <Engine/EventHandler.h>

#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"

void DebugDrawUISystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto MousePos = EventHandler::GetMousePos();
    auto Callback = [&](Entity E, TransformComponent &T,UIButtonComponent &BC)
    {
        auto LineColor = Color(1.0);
        if(BC.Hovered)
            LineColor = Color(1.0,0.0,0.0);
        if(BC.Pressed)
            LineColor = Color(0.0,1.0,0.0);

        RendererRef->DrawRectangleBorders(T.Position,BC.Size,LineColor);
    };
    RendererRef->DrawFilledCircle(MousePos,5);

    CurrentRegistry.MakeView<TransformComponent,UIButtonComponent>().Each(Callback);
}
