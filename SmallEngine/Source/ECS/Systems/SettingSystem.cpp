//
// Created by radov on 14.05.2026.
//

#include "SettingSystem.h"

#include <Engine/App.h>

#include "ECS/Components/PlaySoundRequestComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Components/UITextComponent.h"

SettingSystem::SettingSystem(Registry& R)
{
    auto Settings = App::Get().GetSettings();

    const std::string Font = "Resources/Fonts/PacFont.ttf";
    Vector2f StartingPos = {50,100};
    int i = 0;
    auto OnHoverCall = [&R] (Entity self){ R.GetPool<UITextComponent>().Get(self).FontColor = Color(0.5f);R.AddComponent<PlaySoundRequestComponent>(self).SoundPath = "Resources/Sounds/S_ButtonHover.mp3"; };
    auto OnUnhoverCall = [&R] (Entity self){ R.GetPool<UITextComponent>().Get(self).FontColor = Color(1.0f); };

    for (auto& Line: Settings->Lines)
    {
        const float Ylevel = StartingPos.Y+ (i*50);
        Entity SettingName = R.CreateEntity();
        R.AddComponent<TransformComponent>(SettingName,TransformComponent{{StartingPos.X ,Ylevel},{1,1},{1}});
        R.AddComponent<UITextComponent>(SettingName,UITextComponent{Line->Name, Font,25});

        Entity SettingValue = R.CreateEntity();
        R.AddComponent<TransformComponent>(SettingValue,TransformComponent{{StartingPos.X + 400 ,Ylevel},{1,1},{1}});
        R.AddComponent<UITextComponent>(SettingValue,UITextComponent{Line->GetStringValue(), Font,25});

        auto OnLeft = [&Line,SettingValue,&R] (Entity self){ Line->GoLeft(); R.Get<UITextComponent>(SettingValue).Text = Line->GetStringValue(); };
        Entity LeftButton = R.CreateEntity();
        R.AddComponent<TransformComponent>(LeftButton,TransformComponent{{StartingPos.X + 300 ,Ylevel},{1,1},{1}});
        R.AddComponent<UITextComponent>(LeftButton,UITextComponent{"<", Font,25});
        R.AddComponent<UIButtonComponent>(LeftButton,UIButtonComponent{.OnMouseUp = OnLeft,.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {40,40}});

        auto OnRight = [&Line,SettingValue,&R] (Entity self){ Line->GoRight(); R.Get<UITextComponent>(SettingValue).Text = Line->GetStringValue();};
        Entity RightButton = R.CreateEntity();
        R.AddComponent<TransformComponent>(RightButton,TransformComponent{{StartingPos.X + 700 ,Ylevel},{1,1},{1}});
        R.AddComponent<UITextComponent>(RightButton,UITextComponent{">", Font,25});
        R.AddComponent<UIButtonComponent>(RightButton,UIButtonComponent{.OnMouseUp = OnRight,.OnHover = OnHoverCall,.OnUnhover = OnUnhoverCall,.Size = {40,40}} );

        i++;
    }
}

void SettingSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{

}
