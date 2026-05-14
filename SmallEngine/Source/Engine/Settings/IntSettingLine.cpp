#include "IntSettingLine.h"

IntSettingLine::IntSettingLine(nlohmann::json Config)
{
    Name = Config.at("name").get<std::string>();
    Min = Config.at("min").get<int>();
    Max = Config.at("max").get<int>();
    Step = Config.at("step").get<int>();
    Default = Config.at("default").get<int>();
    Value = Default;
}

void IntSettingLine::LoadFromConfig(nlohmann::json Config)
{
    Value = Config.get<int>();
}

nlohmann::json IntSettingLine::GetConfigValue()
{
    return Value;
}

void IntSettingLine::GoLeft()
{
    Value = std::max(Value - Step,Min);
}

void IntSettingLine::GoRight()
{
    Value = std::min(Value + Step,Max);
}

std::string IntSettingLine::GetStringValue()
{
    return std::to_string(Value);
}

