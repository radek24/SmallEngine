//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <string>

#include "Math/MathForward.h"

struct WindowSpecification {
    std::string Name;
    Vector2i Size;
    bool IsResizable = true;
};


struct Specifications
{
    std::string AppName;
    int ArgumentCount;
    char** Arguments;
    WindowSpecification WindowSpecs;
};

