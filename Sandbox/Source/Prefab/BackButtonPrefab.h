//
// Created by Radovan Šťastný on 21.04.2026.
//

#pragma once
#include <ECS/Entity.h>
#include <ECS/Registry.h>
#include <Engine/App.h>

#include "ECS/Components/PlaySoundRequestComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Components/UITextComponent.h"


class BackButtonPrefab
{
public:
    template <typename T>
    static Entity Create(Registry& R);
};

template<typename T>
Entity BackButtonPrefab::Create(Registry& R)
{
    auto E = R.CreateEntity();
    auto OnHoverCall   = [&R] (Entity self){ R.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f);R.AddComponent<PlaySoundRequestComponent>(self).SoundPath = "Resources/Sounds/S_ButtonHover.mp3"; };
    auto OnUnhoverCall = [&R] (Entity self){ R.GetPool<UITextComponent>().Get(self).FontColor = Color(1.0f); };
    auto OnClick = [] (Entity self){App::Get().QueueLevelTransition<T>();};
    R.AddComponent<TransformComponent>(E, TransformComponent{ .Position = {50, 800} });
    R.AddComponent<UITextComponent>(E,UITextComponent{.Text ="Back", .FontPath = "Resources/Fonts/PacFont.ttf", .FontSize = 25});
    R.AddComponent<UIButtonComponent>(E,UIButtonComponent{.OnMouseUp = OnClick,.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {300,40}});

    return E;
}
