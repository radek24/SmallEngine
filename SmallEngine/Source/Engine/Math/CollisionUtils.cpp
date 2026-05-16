//
// Created by Radovan Šťastný on 20.04.2026.
//

#include "CollisionUtils.h"

bool CollisionUtils::IsPointInsideRectangle(const Vector2f& Point, const Vector2f &TopLeft, const Vector2f &BottomRight)
{
    return (Point > TopLeft && Point < BottomRight);
}
