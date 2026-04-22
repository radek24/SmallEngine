//
// Created by radov on 22.04.2026.
//

#include "SoundSystem.h"

#include <ECS/Registry.h>
#include <Engine/App.h>

#include "ECS/Components/PlaySoundRequestComponent.h"

void SoundSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto Callback = [DeltaTime, this, &CurrentRegistry](Entity E, PlaySoundRequestComponent &SC)
    {
        App::Get().GetSoundManager()->SetVolume(SC.Volume);
        App::Get().GetSoundManager()->Play(SC.SoundPath);
        CurrentRegistry.GetPool<PlaySoundRequestComponent>().Remove(E);
    };
    CurrentRegistry.MakeView<PlaySoundRequestComponent>().Each(Callback);
}
