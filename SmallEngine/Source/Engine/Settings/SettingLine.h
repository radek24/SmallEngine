//
// Created by radov on 14.05.2026.
//


#pragma once
#include <string>
#include <json/json.hpp>
#include "Engine/Core.h"

/** Line of settings for setting manager, inherit this type to create custom settings  */
class SE_API SettingLine
{
public:
    virtual ~SettingLine() = default;
    /** Display name and id of this setting*/
    std::string Name;

    /** Load value from existing player config into this line*/
    virtual void LoadFromConfig(nlohmann::json Config)=0;
    /** Gets config value of this line for save, should only return a simple value, not a object*/
    virtual nlohmann::json GetConfigValue()=0;
    /** Move to the left*/
    virtual void GoLeft()=0;
    /** Move to the right*/
    virtual void GoRight()=0;
    /** Gets display name for this setting value*/
    virtual std::string GetStringValue()=0;
};
