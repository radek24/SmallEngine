#include "FloatSettingLine.h"


double RoundTo(double Value, int Decimals)
{
    double Factor = std::pow(10.0, Decimals);
    return std::round(Value * Factor) / Factor;
}

FloatSettingLine::FloatSettingLine(nlohmann::json Config)
{
    Name = Config.at("name").get<std::string>();
    Min = Config.at("min").get<float>();
    Max = Config.at("max").get<float>();
    Step = Config.at("step").get<float>();
    Default = Config.at("default").get<float>();
    Precision = Config.at("precision").get<int>();
    Value = Default;
}

void FloatSettingLine::LoadFromConfig(nlohmann::json Config)
{
    Value = Config.get<float>();
}

nlohmann::json FloatSettingLine::GetConfigValue()
{
    return Value;
}

void FloatSettingLine::GoLeft()
{
    Value = std::max(Value - Step,Min);
}

void FloatSettingLine::GoRight()
{
    Value = std::min(Value + Step,Max);
}

std::string FloatSettingLine::GetStringValue()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(Precision) << Value;
    std::string s = oss.str();
    return oss.str();
}

