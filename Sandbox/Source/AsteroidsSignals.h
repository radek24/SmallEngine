#pragma once
#include "Engine/Signals/SignalManager.h"

static constexpr const char* Signal_WaveCleared  = "wave.cleared";
static constexpr const char* Signal_BulletFired  = "bullet.fired";
static constexpr const char* Signal_ScoreChanged = "score.changed";
static constexpr const char* Signal_LivesChanged = "lives.changed";

struct ScoreChangedPayload : SignalPayload { int NewScore = 0; };
struct LivesChangedPayload : SignalPayload { int NewLives = 0; };