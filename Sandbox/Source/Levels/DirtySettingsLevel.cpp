//
// Created by radov on 15.05.2026.
//

#include "DirtySettingsLevel.h"

#include <Engine/App.h>

#include "MainMenuLevel.h"
#include "SettingLevel.h"
#include "ECS/Components/PlaySoundRequestComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"
#include "ECS/Systems/UITextEffectSystem.h"

void DirtySettingsLevel::OnEnter()
{
    Level::OnEnter();

    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<UITextEffectSystem>();
    CurrentRegistry.AddSystem<SoundSystem>();

    auto OnHoverCall   = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f); CurrentRegistry.AddComponent<PlaySoundRequestComponent>(self).SoundPath = "Resources/Sounds/S_ButtonHover.mp3"; };
    auto OnUnhoverCall = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(1.0f); };
    Prefab ClickableButton;
    ClickableButton.Add<TransformComponent>({{20.0f, 50.0f},{1.0f, 1.0f},{0.0f}});
    ClickableButton.Add<UITextComponent>({.FontPath = "Resources/Fonts/PacFont.ttf",.FontSize = 25,.FontColor = Color(1.0f)});
    ClickableButton.Add<UIButtonComponent>({.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {400,30}});

    Entity GameTitle = CurrentRegistry.CreateEntity();
    CurrentRegistry.AddComponent<TransformComponent>(GameTitle,TransformComponent{Vector2f(20,20)});
    CurrentRegistry.AddComponent<UITextComponent>(GameTitle,UITextComponent{"YOU HAVE UNSAVED SETTINGS", "Resources/Fonts/PacFont.ttf",30,Color(1.0)});

    auto OnClickSave = [this] (Entity self) {App::Get().GetSettings()->SaveToFile();  App::Get().QueueLevelTransition<MainMenuLevel>();};
    Entity SaveSettingsButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(SaveSettingsButton).Position += Vector2f(0,40);
    CurrentRegistry.Get<UITextComponent>(SaveSettingsButton).Text = "Save settings";
    CurrentRegistry.Get<UIButtonComponent>(SaveSettingsButton).OnMouseUp = OnClickSave;

    auto GoBackAction = [this] (Entity self) {App::Get().QueueLevelTransition<SettingLevel>();};
    Entity BackButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(BackButton).Position += Vector2f(0,80);
    CurrentRegistry.Get<UITextComponent>(BackButton).Text = "Go Back";
    CurrentRegistry.Get<UIButtonComponent>(BackButton).OnMouseUp = GoBackAction;

    auto DiscardAction = [this] (Entity self) {App::Get().GetSettings()->Discard(); App::Get().QueueLevelTransition<MainMenuLevel>();};
    Entity DiscardButton = ClickableButton.Instantiate(CurrentRegistry);
    CurrentRegistry.Get<TransformComponent>(DiscardButton).Position += Vector2f(0,120);
    CurrentRegistry.Get<UITextComponent>(DiscardButton).Text = "Discard changes";
    CurrentRegistry.Get<UIButtonComponent>(DiscardButton).OnMouseUp = DiscardAction;

}
