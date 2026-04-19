//
// Created by radov on 19.04.2026.
//


#pragma once
#include <string>
#include <Engine/Math/Color.h>

struct ScreenSpaceTextComponent
{
    std::string Text;
    std::string FontPath;
    int FontSize = 16;
    Color FontColor = Color(1.0f);
    bool Visible = true;
};
