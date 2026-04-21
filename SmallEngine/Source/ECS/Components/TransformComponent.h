//
// Created by radov on 19.04.2026.
//

#pragma once
#include "Engine/Math/Transform.h"

struct TransformComponent {
    Vector2f Position ={0,0};
    Vector2f Scale = {1,1};
    Rotator Rotation = {0};
};
