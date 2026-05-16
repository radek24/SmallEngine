//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include "MathForward.h"


class CollisionUtils
{
public:
    [[nodiscard]] static bool IsPointInsideRectangle(const Vector2f& Point, const Vector2f &TopLeft, const Vector2f &BottomRight);
};
