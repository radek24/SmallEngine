//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <string>

struct WindowSpecification {
    std::string Name;
    int Width = 500;
    int Height = 300;
    bool IsResizable = true;
};


struct Specifications
{
    std::string AppName;
    int ArgumentCount;
    char** Arguments;
    WindowSpecification WindowSpecs;
};

