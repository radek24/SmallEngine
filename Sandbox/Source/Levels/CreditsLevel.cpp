//
// Created by Radovan Šťastný on 21.04.2026.
//

#include "CreditsLevel.h"

#include <Engine/App.h>

#include "MainMenuLevel.h"
#include "../Prefab/BackButtonPrefab.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"

void CreditsLevel::OnEnter()
{
    Level::OnEnter();
    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(),*Textures);
    App::Get().GetRenderer()->SetClearColor(Color(0.0));
    Prefab Text;
    Text.Add<TransformComponent>({{20.0f, 50.0f},{1.0f, 1.0f}});
    Text.Add<UITextComponent>({.Text = "",.FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 25});

    int i = 0;
    for (const auto& text :Credits)
    {
        auto TextEntity = Text.Instantiate(CurrentRegistry);
        CurrentRegistry.Get<UITextComponent>(TextEntity).Text = text;
        CurrentRegistry.Get<TransformComponent>(TextEntity).Position.Y += (i*40);
        i++;
    }
    BackButtonPrefab::Create<MainMenuLevel>(CurrentRegistry);
}
