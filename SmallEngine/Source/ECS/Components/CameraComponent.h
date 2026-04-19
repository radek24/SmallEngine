//
// Created by radov on 19.04.2026.
//

#pragma once
#include <Engine/Math/MathForward.h>

class CameraComponent
{
    Vector2f Offset = {0, 0};
    float Zoom = 1.0f;
    bool IsActive = true;
};
