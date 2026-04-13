//
// Created by Radovan Šťastný on 11.04.2026.
//

#pragma once
#include "MathForward.h"
#include "Rotator.h"

struct Transform
{
    Vector2f Position;
    Vector2f Scale;
    Rotator Rotation;
};
