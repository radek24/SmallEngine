//
// Created by Radovan Šťastný on 11.04.2026.
//

#pragma once
#include <Engine/DebugBreaks.h>

struct Rotator {

private:
    float Angle;
public:
    [[nodiscard]] float GetAngleDegrees() const {return Angle;}
    //TODO: This PI should be a constant
    [[nodiscard]] float GetAngleRadians() const { return Angle * (3.14159265359f / 180.0f); }

    void SetAngleDegrees(float Angle) {this->Angle = Angle;}
    void SetAngleRadians(float Angle) { this->Angle = Angle * (180.0f / 3.14159265359f); }

    Rotator(){Angle = 0;}
    Rotator(float Angle) {this->Angle = Angle;} // NOLINT(*-explicit-constructor)


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
    Angle += V.Angle;
    return *this;
}

inline Rotator Rotator::operator-=(const Rotator &V)
{
    Angle -= V.Angle;
    return *this;
}
