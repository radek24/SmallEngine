#include <doctest/doctest.h>
#include <Engine/Math/MathForward.h>

static constexpr float EPSILON = 1e-4f;

TEST_CASE("Vector2f - constructors")
{
    SUBCASE("XY constructor") {
        Vector2f v(3.0f, 4.0f);
        CHECK(v.X == 3.0f);
        CHECK(v.Y == 4.0f);
    }
    SUBCASE("Single value constructor")
    {
        Vector2f v(5.0f);
        CHECK(v.X == 5.0f);
        CHECK(v.Y == 5.0f);
    }
    SUBCASE("Copy constructor")
    {
        Vector2f a(1.0f, 2.0f);
        Vector2f b(a);
        CHECK(b.X == 1.0f);
        CHECK(b.Y == 2.0f);
    }
}

TEST_CASE("Vector2f - ZeroVector")
{
    CHECK(Vector2f::ZeroVector.X == 0.0f);
    CHECK(Vector2f::ZeroVector.Y == 0.0f);
}

TEST_CASE("Vector2f - arithmetic")
{
    Vector2f a(3.0f, 4.0f);
    Vector2f b(1.0f, 2.0f);

    SUBCASE("addition")
    {
        Vector2f r = a + b;
        CHECK(r.X == 4.0f);
        CHECK(r.Y == 6.0f);
    }
    SUBCASE("subtraction")
    {
        Vector2f r = a - b;
        CHECK(r.X == 2.0f);
        CHECK(r.Y == 2.0f);
    }
    SUBCASE("scalar multiply")
    {
        Vector2f r = a * 2.0f;
        CHECK(r.X == 6.0f);
        CHECK(r.Y == 8.0f);
    }
    SUBCASE("scalar divide")
    {
        Vector2f r = a / 2.0f;
        CHECK(r.X == 1.5f);
        CHECK(r.Y == 2.0f);
    }
    SUBCASE("component-wise multiply")
    {
        Vector2f r = a * b;
        CHECK(r.X == 3.0f);
        CHECK(r.Y == 8.0f);
    }
    SUBCASE("component-wise divide")
    {
        Vector2f r = a / b;
        CHECK(r.X == 3.0f);
        CHECK(r.Y == 2.0f);
    }
    SUBCASE("negation")
    {
        Vector2f r = -a;
        CHECK(r.X == -3.0f);
        CHECK(r.Y == -4.0f);
    }
    SUBCASE("+=")
    {
        a += b;
        CHECK(a.X == 4.0f);
        CHECK(a.Y == 6.0f);
    }
    SUBCASE("-=")
    {
        a -= b;
        CHECK(a.X == 2.0f);
        CHECK(a.Y == 2.0f);
    }
}

TEST_CASE("Vector2f - dot product")
{
    CHECK(Vector2f::DotProduct({1.0f, 0.0f}, {0.0f, 1.0f}) == doctest::Approx(0.0f));
    CHECK(Vector2f::DotProduct({1.0f, 0.0f}, {1.0f, 0.0f}) == doctest::Approx(1.0f));
    CHECK(Vector2f::DotProduct({3.0f, 4.0f}, {1.0f, 2.0f}) == doctest::Approx(11.0f));
}

TEST_CASE("Vector2f - length")
{
    SUBCASE("Length of (3, 4) is 5")
    {
        CHECK(Vector2f(3.0f, 4.0f).Length() == doctest::Approx(5.0f));
    }
    SUBCASE("LengthSquared of (3, 4) is 25")
    {
        CHECK(Vector2f(3.0f, 4.0f).LengthSquared() == doctest::Approx(25.0f));
    }
    SUBCASE("Zero vector has length 0")
    {
        CHECK(Vector2f(0.0f, 0.0f).Length() == doctest::Approx(0.0f));
    }
}

TEST_CASE("Vector2f - GetRotated") {
    SUBCASE("90 degrees around origin")
    {
        Vector2f r = Vector2f(1.0f, 0.0f).GetRotated(Vector2f::ZeroVector, Rotator(90.0f));
        CHECK(r.X == doctest::Approx(0.0f).epsilon(EPSILON));
        CHECK(r.Y == doctest::Approx(1.0f).epsilon(EPSILON));
    }
    SUBCASE("180 degrees around origin")
    {
        Vector2f r = Vector2f(1.0f, 0.0f).GetRotated(Vector2f::ZeroVector, Rotator(180.0f));
        CHECK(r.X == doctest::Approx(-1.0f).epsilon(EPSILON));
        CHECK(r.Y == doctest::Approx(0.0f).epsilon(EPSILON));
    }
    SUBCASE("0 degrees returns same vector")
    {
        Vector2f r = Vector2f(3.0f, 4.0f).GetRotated(Vector2f::ZeroVector, Rotator(0.0f));
        CHECK(r.X == doctest::Approx(3.0f).epsilon(EPSILON));
        CHECK(r.Y == doctest::Approx(4.0f).epsilon(EPSILON));
    }
    SUBCASE("rotation around non-origin pivot")
    {
        Vector2f r = Vector2f(2.0f, 1.0f).GetRotated(Vector2f(1.0f, 1.0f), Rotator(90.0f));
        CHECK(r.X == doctest::Approx(1.0f).epsilon(EPSILON));
        CHECK(r.Y == doctest::Approx(2.0f).epsilon(EPSILON));
    }
}

TEST_CASE("Vector2f - comparison")
{
    Vector2f a(2.0f, 3.0f);
    Vector2f b(2.0f, 3.0f);
    Vector2f c(5.0f, 6.0f);

    CHECK(a == b);
    CHECK(a != c);
    CHECK(a < c);
    CHECK(c > a);
    CHECK(a <= b);
    CHECK(a >= b);
}