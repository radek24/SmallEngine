//
// Created by Radovan Šťastný on 20.04.2026.
//

#include "UIButtonSystem.h"

#include <ECS/Registry.h>
#include <Engine/EventHandler.h>

#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "Engine/Math/CollisionUtils.h"

void UIButtonSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto MousePos = EventHandler::GetMousePos();
    bool MousePressed = EventHandler::IsMouseButtonHeld(MouseButton::Left);
    auto Callback = [&](Entity E, UIButtonComponent &LC, TransformComponent &TC)
    {
        bool isHovered = CollisionUtils::IsPointInsideRectangle(MousePos, TC.Position, TC.Position + LC.Size);
        bool isPressed = isHovered && MousePressed;

        if (isHovered && !LC.Hovered && LC.OnHover)
            LC.OnHover(E);
        if (!isHovered && LC.Hovered && LC.OnUnhover)
            LC.OnUnhover(E);

        if (isPressed && !LC.Pressed && LC.OnMouseDown)
            LC.OnMouseDown(E);
        if (!isPressed && LC.Pressed && LC.OnMouseUp)
            LC.OnMouseUp(E);

        LC.Hovered = isHovered;
        LC.Pressed = isHovered && MousePressed;
    };
    CurrentRegistry.MakeView<UIButtonComponent,TransformComponent>().Each(Callback);
}
