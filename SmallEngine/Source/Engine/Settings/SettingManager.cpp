//
// Created by radov on 14.05.2026.
//

#include "SettingManager.h"

#include <fstream>

void SettingManager::LoadFromDefaultConfig(const std::string &config)
{
    std::ifstream in(config);
    nlohmann::json Config = nlohmann::json::parse(in);
    LoadFromJson(Config);
}

void SettingManager::LoadFromJson(const nlohmann::json& config)
{
    for(const auto& Entry : config.at("entries"))
    {
        if(Entry["type"] == "int")
            AddLine(std::make_unique<IntSettingLine>(Entry));
        else if(Entry["type"] == "enum")
            AddLine(std::make_unique<EnumSettingLine>(Entry));
    }
}

void SettingManager::LoadConfig(const std::string &config)
{
    ConfigPath = config;
    std::ifstream in(config);
    nlohmann::json Config;
    try {
        Config = nlohmann::json::parse(in);
    } catch (const nlohmann::json::parse_error& e)
    {
        LOG_WARN("Could not parse config, can be just because it's empty for now.");
        return;
    }

    for (auto& [name, value] : Config.items())
    {
        for (auto& Line : Lines)
        {
            if (Line->Name == name)
            {
                Line->LoadFromConfig(value);
                break;
            }
        }
    }
}

bool SettingManager::IsDirty()
{
    std::ifstream in(ConfigPath);
    nlohmann::json Config;
    try {
        Config = nlohmann::json::parse(in);
    } catch (const nlohmann::json::parse_error& e)
    {
        return true;
    }

    for (auto& [name, value] : Config.items())
    {
        for (auto& Line : Lines)
        {
            if (Line->Name == name)
            {
                if(Line->GetConfigValue().dump() != value.dump())
                    return true;
                break;
            }
        }
    }
    return false;
}

void SettingManager::SaveToFile()
{
    nlohmann::json values = nlohmann::json::object();
    for (auto& Line: Lines)
        values[Line->Name] = Line->GetConfigValue();

    LOG_INFO("Saving settings to {0}",ConfigPath);

    std::ofstream file(ConfigPath);
    file << values.dump(4);
}

void SettingManager::Discard()
{
    LoadConfig(ConfigPath);
}

void SettingManager::AddLine(std::unique_ptr<SettingLine> Line)
{
    Lines.emplace_back(std::move(Line));
}
