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
    bool MousePressed = EventHandler::IsMouseButtonHeld(SDL_BUTTON_LEFT);
    auto Callback = [&](Entity E, UIButtonComponent &LC, TransformComponent &TC)
    {
        if (CollisionUtils::IsPointInsideRectangle(MousePos,TC.Transform.Position,TC.Transform.Position + LC.Size))
        {
            LOG_INFO("Mouse in point");
        }
    };
    CurrentRegistry.MakeView<UIButtonComponent,TransformComponent>().Each(Callback);
}
