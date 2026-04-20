//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include <Engine/Math/MathForward.h>

struct BoxShape
{
    Vector2f HalfExtents = Vector2f(10.0f);
};

struct CircleShape
{
    float Radius = 10;
};

struct ColliderComponent
{
    Vector2f Offset = { 0.0f, 0.0f };
    std::variant<BoxShape, CircleShape> Shape = CircleShape();
    bool GenerateOverlap = false;
};
