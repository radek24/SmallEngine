//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <string>

#include "Math/MathForward.h"

enum LogicalPresentation
{
    Letterbox,
    Stretch,
    OverScan,
    Disabled
};

struct WindowSpecification {
    std::string Name;
    Vector2i Size;
    bool IsResizable = true;
    bool IsBorderless = false;
    bool IsFullscreen = false;
    LogicalPresentation Presentation = Disabled;
    std::string WindowIcon = "Resources/Textures/T_Icon.png";
};

struct Specifications
{
    std::string AppName;
    int ArgumentCount;
    char** Arguments;
    WindowSpecification WindowSpecs;
};

