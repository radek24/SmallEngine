//
// Created by radov on 14.05.2026.
//


#pragma once
#include <string>
#include <json/json.hpp>
#include "Engine/Core.h"


class SE_API SettingLine
{
public:
    virtual ~SettingLine() = default;

    std::string Name;

    virtual void LoadFromConfig(nlohmann::json Config)=0;
    virtual nlohmann::json GetConfigValue()=0;
    virtual void GoLeft()=0;
    virtual void GoRight()=0;
    virtual std::string GetStringValue()=0;
};
