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

struct WindowSpecification
{
    /** This will be the window title*/
    std::string Name;
    Vector2i Size;
    bool IsResizable = true;
    bool IsBorderless = false;
    bool IsFullscreen = false;
    /** How to handle window resizing */
    LogicalPresentation Presentation = Disabled;
    std::string WindowIcon = "Resources/Textures/T_Icon.png";
};

struct Specifications
{
    /** Used for internal identification and such */
    std::string AppName;
    int ArgumentCount;
    char** Arguments;
    WindowSpecification WindowSpecs;
    std::string SettingConfigPath = "Resources/Data/SettingsConfig.json";
    std::string SettingPath = "Settings.json";
};

