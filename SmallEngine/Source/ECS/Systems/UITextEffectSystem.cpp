//
// Created by radov on 21.04.2026.
//

#include "UITextEffectSystem.h"

#include <ECS/Registry.h>

#include "ECS/Components/RainbowTextEffectComponent.h"
#include "ECS/Components/UITextComponent.h"

void UITextEffectSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [DeltaTime](Entity E, RainbowTextEffectComponent &R,UITextComponent &T)
    {
        T.FontColor = Color::FromHSV(R.CurrentHue,R.Saturation,R.Value);
        R.CurrentHue += R.Speed * DeltaTime;
    };
    CurrentRegistry.MakeView<RainbowTextEffectComponent, UITextComponent>().Each(Callback);
}
