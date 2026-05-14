//
// Created by radov on 14.05.2026.
//


#pragma once
#include "SettingLine.h"
#include "Engine/Core.h"


class SE_API IntSettingLine : public SettingLine
{

public:
  IntSettingLine(nlohmann::json Config);

  int Value;
  int Default;
  int Min=0;
  int Max=10;
  int Step=1;

  void LoadFromConfig(nlohmann::json Config) override;
  nlohmann::json GetConfigValue() override;
  void GoLeft() override;
  void GoRight() override;
  std::string GetStringValue() override;
};
