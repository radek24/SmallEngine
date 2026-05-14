#include "EnumSettingLine.h"

#include <utility>

EnumSettingLine::EnumSettingLine(nlohmann::json Config)
{
    Name = Config.at("name").get<std::string>();
    for (const auto& Option: Config.at("options"))
        Options.emplace_back(Option.get<std::string>());

    DefaultOption = Config.at("default").get<int>();
    CurrentOptionIndex = DefaultOption;
}

std::string EnumSettingLine::GetSelectedOption()
{
    return Options[CurrentOptionIndex];
}

void EnumSettingLine::LoadFromConfig(nlohmann::json Config)
{
    CurrentOptionIndex = Config.get<int>();
}

nlohmann::json EnumSettingLine::GetConfigValue()
{
    return CurrentOptionIndex;
}

void EnumSettingLine::GoLeft()
{
    CurrentOptionIndex = std::max(CurrentOptionIndex-1, 0);
}
void EnumSettingLine::GoRight()
{
    CurrentOptionIndex = std::min(CurrentOptionIndex+1, (int)Options.size()-1);
}

std::string EnumSettingLine::GetStringValue()
{
    return Options[CurrentOptionIndex];
}
