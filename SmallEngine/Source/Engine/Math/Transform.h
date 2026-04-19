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

    static Transform Default()
    {
        return { {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f} };
    }

    static Transform At(const Vector2f& InPosition)
    {
        return { InPosition, {1.0f, 1.0f}, {0.0f} };
    }
};
