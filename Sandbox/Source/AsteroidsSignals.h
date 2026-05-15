#pragma once
#include "Engine/Signals/SignalManager.h"

static constexpr const char* Signal_AsteroidDestroyed = "asteroid.destroyed";
static constexpr const char* Signal_PlayerDamaged = "player.damaged";

struct AsteroidDestroyedPayload : SignalPayload
{
    int Points = 0;
};