//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include "MathForward.h"


class CollisionUtils
{
public:
    [[nodiscard]] static bool IsPointInsideRectangle(Vector2f Point, Vector2f TopLeft,Vector2f BottomRight);
private:

};
