#pragma once
#include "ECS/System.h"
#include "Engine/Signals/SignalManager.h"

class AsteroidsSoundSystem : public System
{
public:
    AsteroidsSoundSystem();
    ~AsteroidsSoundSystem() override;

    void Update(Registry&, float) override {}
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::PostUpdate; }

private:
    SubscriptionId ScoreSubId = 0;
    SubscriptionId LivesSubId = 0;
    SubscriptionId WaveSubId  = 0;
    SubscriptionId FireSubId  = 0;
};
