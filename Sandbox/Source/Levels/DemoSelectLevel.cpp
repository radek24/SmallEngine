//
// Created by radov on 21.04.2026.
//

#include "DemoSelectLevel.h"

#include <Engine/App.h>

#include "ComponentShowcase.h"
#include "MainMenuLevel.h"
#include "../Prefab/BackButtonPrefab.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"


struct DemoButtonInfo
{
    std::string Name;
    std::function<void(Entity self)> Action;
};
std::vector<DemoButtonInfo>  ButtonInfos =
{
    {"Component Showcase", [] (Entity self) {App::Get().QueueLevelTransition<ComponentShowcase>();}},
    {"Boids", [] (Entity self) {App::Get().QueueLevelTransition<MainMenuLevel>();}},
    {"Space Invaders", [] (Entity self) {App::Get().QueueLevelTransition<MainMenuLevel>();}},
    {"Particles", [] (Entity self) {App::Get().QueueLevelTransition<MainMenuLevel>();}}

};


void DemoSelectLevel::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.0f));

    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(),*Textures);

    BackButtonPrefab::Create<MainMenuLevel>(CurrentRegistry);

    auto OnHoverCall   = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f); };
    auto OnUnhoverCall = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(1); };
    Prefab ClickableButton;
    ClickableButton.Add<TransformComponent>({{20.0f, 50.0f},{1.0f, 1.0f},{0.0f}});
    ClickableButton.Add<UITextComponent>({.FontPath = "Resources/Fonts/PacFont.ttf",.FontSize = 25,.FontColor = Color(1)});
    ClickableButton.Add<UIButtonComponent>({.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {600,30}});

    int i = 0;
    for(auto& ButtonInfo : ButtonInfos)
    {
        Entity NewButton = ClickableButton.Instantiate(CurrentRegistry);
        CurrentRegistry.Get<TransformComponent>(NewButton).Position += Vector2f(0,(60 * i));
        CurrentRegistry.Get<UIButtonComponent>(NewButton).OnMouseUp = ButtonInfo.Action;
        CurrentRegistry.Get<UITextComponent>(NewButton).Text = ButtonInfo.Name;
        i++;
    }


}
