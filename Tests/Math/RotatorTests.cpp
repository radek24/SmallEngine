#include <doctest/doctest.h>
#include <Engine/Math/Rotator.h>

static constexpr float EPSILON = 1e-4f;

TEST_CASE("Rotator - constructors")
{
    SUBCASE("Default constructor gives 0 degrees")
    {
        Rotator r;
        CHECK(r.GetAngleDegrees() == 0.0f);
    }
    SUBCASE("Float constructor")
    {
        Rotator r(90.0f);
        CHECK(r.GetAngleDegrees() == 90.0f);
    }
}

TEST_CASE("Rotator - GetAngleRadians")
{
    CHECK(Rotator(0.0f).GetAngleRadians() == doctest::Approx(0.0f).epsilon(EPSILON));
    CHECK(Rotator(180.0f).GetAngleRadians() == doctest::Approx(3.14159f).epsilon(EPSILON));
    CHECK(Rotator(90.0f).GetAngleRadians() == doctest::Approx(1.5708f).epsilon(EPSILON));
    CHECK(Rotator(360.0f).GetAngleRadians() == doctest::Approx(6.28318f).epsilon(EPSILON));
}

TEST_CASE("Rotator - arithmetic")
{
    Rotator a(90.0f);
    Rotator b(45.0f);

    SUBCASE("addition")
    {
        CHECK_EQ((a + b).GetAngleDegrees(), 135.0f);
    }
    SUBCASE("subtraction")
    {
        CHECK_EQ((a - b).GetAngleDegrees(), 45.0f);
    }
    SUBCASE("scalar multiply")
    {
        CHECK_EQ((a * 2.0f).GetAngleDegrees(), 180.0f);
    }
    SUBCASE("scalar divide")
    {
        CHECK_EQ((a / 2.0f).GetAngleDegrees(), 45.0f);
    }
    SUBCASE("negation")
    {
        CHECK_EQ((-a).GetAngleDegrees(), -90.0f);
    }
    SUBCASE("+=")
    {
        a += b;
        CHECK_EQ(a.GetAngleDegrees(), 135.0f);
    }
    SUBCASE("-=")
    {
        a -= b;
        CHECK_EQ(a.GetAngleDegrees(), 45.0f);
    }
}

TEST_CASE("Rotator - SetAngleDegrees")
{
    Rotator r;
    r.SetAngleDegrees(270.0f);
    CHECK_EQ(r.GetAngleDegrees(), 270.0f);
}