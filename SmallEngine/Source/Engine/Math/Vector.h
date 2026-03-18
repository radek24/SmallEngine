//
// Created by radov on 08.03.2026.
//


#pragma once
#include <ostream>
#include <type_traits>
#include <spdlog/fmt/fmt.h>


/*2D vector*/
template <typename T>
struct Vector2 {

    T X;
    T Y;

    /** The number of components this vector type has. */
    static constexpr int NumComponents = 2;

    /** Global 2D zero vector constant (0,0) */
    static const Vector2<T> ZeroVector;

    /* Constructors */
    /** Default constructor (no initialization). */
    [[nodiscard]] Vector2() = default;
    /** Construct vector from X and Y*/
    [[nodiscard]] Vector2<T>(T InX, T InY);
    /** Construct vector from single value*/
    [[nodiscard]] explicit Vector2<T>(T InA);
    /** Copy constructor*/
    [[nodiscard]] Vector2<T>(const Vector2<T>& V);

    /*Math*/
    /** Gets result of adding two vectors*/
    [[nodiscard]] Vector2<T> operator+(const Vector2<T>& V) const;
    /** Gets result of subtracting two vectors*/
    [[nodiscard]] Vector2<T> operator-(const Vector2<T>& V) const;
    /** Scales vector by some value*/
    [[nodiscard]] Vector2<T> operator*(T Scale) const;
    /** Divides vector by some value*/
    [[nodiscard]] Vector2<T> operator/(T Scale) const;
    /** Component - wise multiply */
    Vector2<T> operator*(const Vector2<T>& V) const;
    /** Component - wise divide */
    Vector2<T> operator/(const Vector2<T>& V) const;
    /** Negates vector*/
    Vector2<T> operator-() const;
    /** Add another vector to this one */
    Vector2<T> operator+=(const Vector2<T>& V) const;
    /** Subtracts another vector from this one */
    Vector2<T> operator-=(const Vector2<T>& V) const;
    /* Currently missing operator : += -= /= *= */

    /** Returns dot product of two vectors*/
    [[nodiscard]] static T DotProduct(const Vector2<T>& A, const Vector2<T>& B);
    /** Returns length of this vector*/
    [[nodiscard]] T Length() const;
    /** Normalize vector IN-PLACE */
    void Normalize() const;
    /** Gets Normalized vector, doesn't change source */
    [[nodiscard]] Vector2<T> GetNormalized();


    /* Compares */
    /** Compares vector to another*/
    [[nodiscard]] bool operator==(const Vector2<T>& V) const;
    /** Compares vector to another*/
    [[nodiscard]] bool operator!=(const Vector2<T>& V) const;


    /** Print operator*/
    friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& V)
    {
        return os << "(" << V.X << ", " << V.Y << ")";
    }

};

template<typename T>
Vector2<T>::Vector2(T InX, T InY) : X(InX),Y(InY){}

template<typename T>
Vector2<T>::Vector2(T InA) : X(InA),Y(InA){}

template<typename T>
Vector2<T>::Vector2(const Vector2<T> &V):X(V.X),Y(V.Y){}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T> &V) const
{
    return Vector2<T>(X+V.X,Y+V.Y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T> &V) const
{
    return Vector2<T>(X-V.X,Y-V.Y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T Scale) const
{
    return Vector2<T>(X*Scale,Y*Scale);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(T Scale) const
{
    return Vector2<T>(X/Scale,Y/Scale);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T> &V) const
{
    return Vector2<T>(X*V.X,Y*V.Y);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T> &V) const
{
    return Vector2<T>(X/V.X,Y/V.Y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-() const
{
    return Vector2<T>(-X, -Y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2<T> &V) const
{
    X += V.X; Y += V.Y;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2<T> &V) const
{
    X -= V.X; Y -= V.Y;
    return *this;
}

template<typename T>
T Vector2<T>::DotProduct(const Vector2<T> &A, const Vector2<T> &B)
{
    return A.X*B.X + A.Y*B.Y;
}

template<typename T>
T Vector2<T>::Length() const
{
    return sqrtf((X*X) + (Y*Y));
}

template<typename T>
void Vector2<T>::Normalize() const
{
    const T Scale = this->Length();
    X *= Scale;
    Y *= Scale;
}

template<typename T>
Vector2<T> Vector2<T>::GetNormalized()
{
    Vector2 Out = this;
    Out.Normalize();
    return Out;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T> &V) const
{
    return X==V.X && Y==V.Y;
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T> &V) const
{
    return !(this == V);
}
template <typename Type>
inline const Vector2<Type> Vector2<Type>::ZeroVector = {Type(0), Type(0)};

/** Formatter for {0} style printing */
template <typename T>
struct fmt::formatter<Vector2<T>>
{
    constexpr auto parse(fmt::format_parse_context& ctx)
    {
        return ctx.begin();
    }
    auto format(const Vector2<T>& v, fmt::format_context& ctx) const
    {
        return fmt::format_to(ctx.out(), "({}, {})", v.X, v.Y);
    }
};