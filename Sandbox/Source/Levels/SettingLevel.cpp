#include "SettingLevel.h"

#include <Engine/App.h>
#include <Engine/Input/EventHandler.h>

#include "DirtySettingsLevel.h"
#include "MainMenuLevel.h"
#include "../Prefab/BackButtonPrefab.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Systems/SettingSystem.h"
#include "ECS/Systems/SoundSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"

void SettingLevel::OnEnter()
{
    Level::OnEnter();
    App::Get().GetRenderer()->SetClearColor(Color(0.0f));

    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
    CurrentRegistry.AddSystem<SoundSystem>();
    CurrentRegistry.AddSystem<SettingSystem>(CurrentRegistry);

    auto E = CurrentRegistry.CreateEntity();
    auto OnHoverCall = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f);CurrentRegistry.AddComponent<PlaySoundRequestComponent>(self).SoundPath = "Resources/Sounds/S_ButtonHover.mp3"; };
    auto OnUnhoverCall = [this] (Entity self){ CurrentRegistry.GetPool<UITextComponent>().Get(self).FontColor = Color(1.0f); };
    auto OnClick = [] (Entity self){App::Get().GetSettings()->SaveToFile();};
    CurrentRegistry.AddComponent<TransformComponent>(E, TransformComponent{ .Position = {500, 800} });
    CurrentRegistry.AddComponent<UITextComponent>(E,UITextComponent{.Text ="Save Settings", .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 25});
    CurrentRegistry.AddComponent<UIButtonComponent>(E,UIButtonComponent{.OnMouseUp = OnClick,.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {300,30}});

    auto Back = CurrentRegistry.CreateEntity();
    auto OnBackClick = [] (Entity self)
    {
        if(App::Get().GetSettings()->IsDirty())
        {
            App::Get().QueueLevelTransition<DirtySettingsLevel>();
            return;
        }
        App::Get().QueueLevelTransition<MainMenuLevel>();
    };
    CurrentRegistry.AddComponent<TransformComponent>(Back, TransformComponent{ .Position = {50, 800} });
    CurrentRegistry.AddComponent<UITextComponent>(Back,UITextComponent{.Text ="Back", .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 25});
    CurrentRegistry.AddComponent<UIButtonComponent>(Back,UIButtonComponent{.OnMouseUp = OnBackClick,.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {300,40}});

}