//
// Created by radov on 14.05.2026.
//


#pragma once
#include "SettingLine.h"
#include "Engine/Core.h"


class SE_API FloatSettingLine : public SettingLine
{

public:
  FloatSettingLine(nlohmann::json Config);

  float Value;
  float Default;
  float Min=0;
  float Max=10;
  float Step=1;
  int Precision=1;

  void LoadFromConfig(nlohmann::json Config) override;
  nlohmann::json GetConfigValue() override;
  void GoLeft() override;
  void GoRight() override;
  std::string GetStringValue() override;
};
