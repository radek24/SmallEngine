//
// Created by Radovan Šťastný on 20.04.2026.
//

#include "CollisionUtils.h"

bool CollisionUtils::IsPointInsideRectangle(Vector2f Point, Vector2f TopLeft, Vector2f BottomRight)
{
    return (Point > TopLeft && Point < BottomRight);
}
