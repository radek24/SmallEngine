//
// Created by radov on 09.03.2026.
//

#include "MathUtils.h"

float MathUtils::Integer8ToFloat(const uint8_t Integer)
{
    return (static_cast<float>(Integer)/255.0f);
}

uint8_t MathUtils::FloatToInteger8(float Value)
{
    const float Clamped = Value < 0.0f ? 0.0f : (Value > 1.0f ? 1.0f : Value);
    return static_cast<uint8_t>(Clamped * 255.0f);
}
