//
// Created by radov on 09.03.2026.
//


#pragma once

#include <cstdint>
#include "MathUtils.h"

class Color
{
public:
    /** Constructor that takes 0-1 floats instead of ints, will be converted to ints internally*/
    Color(float R, float G, float B,float A);
    /** Constructor that takes 0-1 floats instead of ints, will be converted to ints internally*/
    Color(float R, float G, float B);
    /** Constructor that takes 0-1 floats instead of ints, will be converted to ints internally*/
    explicit Color(float Gray);
    Color();


    [[nodiscard]] float R() const{return MathUtils::Integer8ToFloat(Rint);}
    [[nodiscard]] float G() const{return MathUtils::Integer8ToFloat(Gint);}
    [[nodiscard]] float B() const{return MathUtils::Integer8ToFloat(Bint);}
    [[nodiscard]] float A() const{return MathUtils::Integer8ToFloat(Aint);}

    [[nodiscard]] uint8_t NativeR() const{return Rint;}
    [[nodiscard]] uint8_t NativeG() const{return Gint;}
    [[nodiscard]] uint8_t NativeB() const{return Bint;}
    [[nodiscard]] uint8_t NativeA() const{return Aint;}

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