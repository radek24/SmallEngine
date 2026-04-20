//
// Created by Radovan Šťastný on 20.04.2026.
//

#pragma once
#include <functional>
#include <Engine/Math/MathForward.h>


struct UIButtonComponent
{
    bool Pressed = false;
    bool Hovered = false;

    std::function<void()> OnClick{};
    std::function<void()> OnHover{};
    std::function<void()> OnRelease{};
    //TODO: We currently only support extending size from top left corner, same as UI text. This should be fixed and improved
    Vector2f Size = {100,100};
};
