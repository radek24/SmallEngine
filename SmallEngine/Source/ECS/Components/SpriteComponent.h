//
// Created by radov on 19.04.2026.
//


#pragma once
#include <Engine/Math/Color.h>
#include "Engine/Rendering/TextureManager.h"

enum class Positioning
{
        Center,
        LeftTop,
        RightTop,
        LeftCenter,
        RightCenter,
        LeftBottom,
        RightBottom,
};

struct SpriteComponent
{
        TextureHandle Texture = INVALID_TEXTURE;
        Color Tint = Color(1.0);
        int ZOrder = 0;
        bool Visible = true;
        Positioning Positioning = Positioning::Center;
};
