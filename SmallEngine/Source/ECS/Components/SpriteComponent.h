//
// Created by radov on 19.04.2026.
//


#pragma once
#include <Engine/Math/Color.h>
#include "Engine/Rendering/TextureManager.h"


struct SpriteComponent
{
        TextureHandle Texture = INVALID_TEXTURE;
        Color Tint = Color(1.0);
        //TODO: Add support for SDL_FRect
        int ZOrder = 0;
        bool Visible = true;
};
