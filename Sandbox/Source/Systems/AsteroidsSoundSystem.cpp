#include "AsteroidsSoundSystem.h"

#include <Engine/App.h>
#include <Engine/Sounds/SoundManager.h>
#include "../AsteroidsSignals.h"

AsteroidsSoundSystem::AsteroidsSoundSystem()
{
    auto& SM= *App::Get().GetSignalManager();
    auto* Sound = App::Get().GetSoundManager();

    ScoreSubId = SM.Subscribe(Signal_ScoreChanged, [Sound](SignalPayload&)
    {
        Sound->SetVolume(0.6f);
        Sound->Play("Resources/Sounds/S_Explosion.mp3");
    });

    LivesSubId = SM.Subscribe(Signal_LivesChanged, [Sound](SignalPayload&)
    {
        Sound->SetVolume(1.0f);
        Sound->Play("Resources/Sounds/S_Explosion.mp3");
    });

    WaveSubId = SM.Subscribe(Signal_WaveCleared, [Sound](SignalPayload&)
    {
        Sound->SetVolume(0.8f);
        Sound->Play("Resources/Sounds/S_Win.mp3");
    });

    FireSubId = SM.Subscribe(Signal_BulletFired, [Sound](SignalPayload&)
    {
        Sound->SetVolume(0.4f);
        Sound->Play("Resources/Sounds/S_FireLaser.mp3");
    });
}

AsteroidsSoundSystem::~AsteroidsSoundSystem()
{
    auto& SM = *App::Get().GetSignalManager();
    SM.Unsubscribe(ScoreSubId);
    SM.Unsubscribe(LivesSubId);
    SM.Unsubscribe(WaveSubId);
    SM.Unsubscribe(FireSubId);
}
