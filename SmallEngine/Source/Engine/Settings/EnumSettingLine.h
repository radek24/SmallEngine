//
// Created by radov on 14.05.2026.
//


#pragma once
#include "SettingLine.h"
#include "Engine/Core.h"

class SE_API EnumSettingLine : public SettingLine
{
public:
    EnumSettingLine(nlohmann::json Config);
    std::vector<std::string> Options;
    int DefaultOption;
    int CurrentOptionIndex;

    std::string GetSelectedOption();

    void LoadFromConfig(nlohmann::json Config) override;
    nlohmann::json GetConfigValue() override;
    void GoLeft() override;
    void GoRight() override;
    std::string GetStringValue() override;
};
