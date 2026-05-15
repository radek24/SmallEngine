//
// Created by radov on 14.05.2026.
//


#pragma once
#include <memory>
#include <Engine/DebugBreaks.h>

#include "EnumSettingLine.h"
#include "FloatSettingLine.h"
#include "IntSettingLine.h"
#include "SettingLine.h"
#include "Engine/Core.h"

/** Managers game configuration*/
class SE_API SettingManager
{
public:
    SettingManager() = default;
    SettingManager(const SettingManager&) = delete;
    SettingManager& operator=(const SettingManager&) = delete;
    SettingManager(SettingManager&&) = default;
    SettingManager& operator=(SettingManager&&) = default;

    /** Load this settings layout from config, default values, types, names etc*/
    void LoadFromDefaultConfig(const std::string& config);
    /** Parses settings layout directly from a JSON object */
    void LoadFromJson(const nlohmann::json& config);
    /** Tries to load actual current values of the settings from config set by player*/
    void LoadConfig(const std::string& config);

    /** Reads value from the settings, you need to match the correct type.*/
    template<typename T>
    T LineValue(const std::string& Name);
    std::vector<std::unique_ptr<SettingLine>> Lines;

    /** Returns if the values in the lines are different that what we have saved in setting*/
    [[nodiscard]] bool IsDirty();

    /** Save all settings into config file*/
    void SaveToFile();
    /** Resets all lines to state from config file, so it isnt dirty, WONT RESET TO DEFAULT */
    void Discard();

private:
    /** Adds line to the settings*/
    void AddLine(std::unique_ptr<SettingLine> Line);

    std::string ConfigPath;
};

template<typename T>
T SettingManager::LineValue(const std::string& Name) {NoEntry();}

template<>
inline int SettingManager::LineValue<int>(const std::string& Name)
{
    for (auto& Line: Lines) {
        if(Line->Name == Name)
            return dynamic_cast<IntSettingLine*>(Line.get())->Value;
    }
    LOG_FATAL("Did not found {0} int setting", Name);
    return 0;
}

template<>
inline std::string SettingManager::LineValue<std::string>(const std::string& Name)
{
    for (auto& Line: Lines) {
        if(Line->Name == Name)
            return dynamic_cast<EnumSettingLine*>(Line.get())->GetSelectedOption();
    }
    LOG_FATAL("Did not found {0} string setting", Name);
    return "";
}

template<>
inline float SettingManager::LineValue<float>(const std::string& Name)
{
    for (auto& Line: Lines) {
        if(Line->Name == Name)
            return dynamic_cast<FloatSettingLine*>(Line.get())->Value;
    }
    LOG_FATAL("Did not found {0} float setting", Name);
    return 0;
}

