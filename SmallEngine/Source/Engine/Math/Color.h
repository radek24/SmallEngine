//
// Created by radov on 09.03.2026.
//


#pragma once

#include <cstdint>
#include "MathUtils.h"
#include "Engine/Core.h"

#define COLOR_TO_SDL(Color) (Color).R8(),(Color).G8(),(Color).B8(),(Color).A8()

class SE_API Color
{
public:
    /** Constructor that takes 0-1 floats instead of ints, will be converted to ints internally*/
    Color(float R, float G, float B,float A);
    /** Constructor that takes 0-1 floats instead of ints, will be converted to ints internally*/
    Color(float R, float G, float B);
    /** Constructor that takes 0-1 floats instead of ints, will be converted to ints internally*/
    explicit Color(float Gray);
    Color();
    /** Returns color constructed from HSV (H => 0-360   S = 0-1  V = 0-1)*/
    static Color FromHSV(float Hue,float Saturation, float Value);

    [[nodiscard]] float RF() const{return MathUtils::Integer8ToFloat(Rint);}
    [[nodiscard]] float GF() const{return MathUtils::Integer8ToFloat(Gint);}
    [[nodiscard]] float BF() const{return MathUtils::Integer8ToFloat(Bint);}
    [[nodiscard]] float AF() const{return MathUtils::Integer8ToFloat(Aint);}

    [[nodiscard]] uint8_t R8() const{return Rint;}
    [[nodiscard]] uint8_t G8() const{return Gint;}
    [[nodiscard]] uint8_t B8() const{return Bint;}
    [[nodiscard]] uint8_t A8() const{return Aint;}

    [[nodiscard]] SDL_Color GetSDLColor() const;

private:
    uint8_t Rint;
    uint8_t Gint;
    uint8_t Bint;
    uint8_t Aint;
};

inline Color::Color(const float R, const float G, const float B, const float A):
Rint(MathUtils::FloatToInteger8(R)),
Gint(MathUtils::FloatToInteger8(G)),
Bint(MathUtils::FloatToInteger8(B)),
Aint(MathUtils::FloatToInteger8(A))
{}

inline Color::Color(const float R, const float G, const float B):
Rint(MathUtils::FloatToInteger8(R)),
Gint(MathUtils::FloatToInteger8(G)),
Bint(MathUtils::FloatToInteger8(B)),
Aint(255)
{}

inline Color::Color(const float Gray):
Rint(MathUtils::FloatToInteger8(Gray)),
Gint(MathUtils::FloatToInteger8(Gray)),
Bint(MathUtils::FloatToInteger8(Gray)),
Aint(255)
{}

inline Color::Color():
Rint(0),
Gint(0),
Bint(0),
Aint(255)
{}

inline Color Color::FromHSV(float Hue, float Saturation, float Value)
{
    Color Result;
    float R, G, B;

    if (Saturation <= 0.0f)
    {
        Result.Rint = MathUtils::FloatToInteger8(Value);
        Result.Gint = MathUtils::FloatToInteger8(Value);
        Result.Bint = MathUtils::FloatToInteger8(Value);
        return Result;
    }

    float H = Hue / 60.0f;
    int   I = static_cast<int>(H);
    float F = H - static_cast<float>(I);
    float P = Value * (1.0f - Saturation);
    float Q = Value * (1.0f - Saturation * F);
    float T = Value * (1.0f - Saturation * (1.0f - F));

    switch (I)
    {
        case 0:  R = Value; G = T;     B = P;     break;
        case 1:  R = Q;     G = Value; B = P;     break;
        case 2:  R = P;     G = Value; B = T;     break;
        case 3:  R = P;     G = Q;     B = Value; break;
        case 4:  R = T;     G = P;     B = Value; break;
        default: R = Value; G = P;     B = Q;     break;
    }

    Result.Rint = MathUtils::FloatToInteger8(R);
    Result.Gint = MathUtils::FloatToInteger8(G);
    Result.Bint = MathUtils::FloatToInteger8(B);
    return Result;
}
inline SDL_Color Color::GetSDLColor() const
{
    return SDL_Color(R8(),G8(),B8(),A8());
}
