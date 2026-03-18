//
// Created by radov on 09.03.2026.
//


#pragma once
#include <cstdint>


class MathUtils
{
public:
  [[nodiscard]] static float Integer8ToFloat(uint8_t Integer);
  [[nodiscard]] static uint8_t FloatToInteger8(float Value);
};
