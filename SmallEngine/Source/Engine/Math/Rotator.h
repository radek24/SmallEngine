//
// Created by Radovan Šťastný on 11.04.2026.
//

#pragma once
#include <Engine/DebugBreaks.h>

#include "MathForward.h"


struct Rotator {

private:
    float Angle;
public:
    [[nodiscard]] float GetAngleDegrees() const {return Angle;}
    [[nodiscard]] float GetAngleRadians() const {Unimplemented();return 0;}

    void SetAngleDegrees(float Angle) {this->Angle = Angle;}
    void SetAngleRadians(float Angle) {Unimplemented()}

    Rotator(){Angle = 0;}
    explicit Rotator(float Angle) {this->Angle = Angle;}


    /*Math*/
    [[nodiscard]] Rotator operator+(const Rotator& V) const;
    [[nodiscard]] Rotator operator-(const Rotator& V) const;
    Rotator operator*(float Scale) const;
    Rotator operator/(float Scale) const;
    Rotator operator-() const;
    Rotator operator+=(const Rotator& V);
    Rotator operator-=(const Rotator& V);
};

inline Rotator Rotator::operator+(const Rotator &V) const
{
    return Rotator(Angle + V.Angle);
}

inline Rotator Rotator::operator-(const Rotator &V) const
{
    return Rotator(Angle - V.Angle);
}

inline Rotator Rotator::operator*(float Scale) const
{
    return Rotator(Angle * Scale);
}

inline Rotator Rotator::operator/(float Scale) const
{
    return Rotator(Angle / Scale);
}

inline Rotator Rotator::operator-() const
{
    return Rotator(-Angle);
}

inline Rotator Rotator::operator+=(const Rotator &V)
{
    Angle =+ V.Angle;
    return *this;
}

inline Rotator Rotator::operator-=(const Rotator &V)
{
    Angle =- V.Angle;
    return *this;
}
