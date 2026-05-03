//
// Created by radov on 22.04.2026.
//

#pragma once
#include "Engine/Math/MathForward.h"

struct ParticleComponent
{
    Vector2f Velocity   = {0, 0};
    float    Damping    = 0.98f;
    float    GravityScale = 1.0f;
};