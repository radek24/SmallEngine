//
// Created by radov on 20.04.2026.
//


#pragma once
#include <Engine/Math/Color.h>


struct BouncyBallComponent
{
    float Size = 20;
    Vector2f Velocity;
    float Damping = 0.9;
};
