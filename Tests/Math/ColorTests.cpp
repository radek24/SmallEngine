#include <doctest/doctest.h>
#include <Engine/Math/Color.h>

TEST_CASE("Color - default constructor")
{
    Color c;
    CHECK(c.R8() == 0);
    CHECK(c.G8() == 0);
    CHECK(c.B8() == 0);
    CHECK(c.A8() == 255);
}

TEST_CASE("Color - RGB float constructor")
{
    Color c(1.0f, 0.0f, 0.0f);
    CHECK(c.R8() == 255);
    CHECK(c.G8() == 0);
    CHECK(c.B8() == 0);
    CHECK(c.A8() == 255);
}

TEST_CASE("Color - RGBA float constructor")
{
    Color c(0.0f, 1.0f, 0.0f, 0.0f);
    CHECK(c.R8() == 0);
    CHECK(c.G8() == 255);
    CHECK(c.B8() == 0);
    CHECK(c.A8() == 0);
}

TEST_CASE("Color - gray constructor")
{
    Color c(1.0f);
    CHECK(c.R8() == 255);
    CHECK(c.G8() == 255);
    CHECK(c.B8() == 255);
    CHECK(c.A8() == 255);
}

TEST_CASE("Color - float accessors round-trip")
{
    Color black(0.0f, 0.0f, 0.0f, 0.0f);
    CHECK(black.RF() == doctest::Approx(0.0f).epsilon(0.01f));
    CHECK(black.AF() == doctest::Approx(0.0f).epsilon(0.01f));

    Color white(1.0f, 1.0f, 1.0f, 1.0f);
    CHECK(white.RF() == doctest::Approx(1.0f).epsilon(0.01f));
    CHECK(white.GF() == doctest::Approx(1.0f).epsilon(0.01f));
    CHECK(white.BF() == doctest::Approx(1.0f).epsilon(0.01f));
    CHECK(white.AF() == doctest::Approx(1.0f).epsilon(0.01f));
}

TEST_CASE("Color - FromHSV primary colors")
{
    SUBCASE("red H=0")
    {
        Color c = Color::FromHSV(0.0f, 1.0f, 1.0f);
        CHECK(c.R8() == 255);
        CHECK(c.G8() == 0);
        CHECK(c.B8() == 0);
    }
    SUBCASE("green H=120")
    {
        Color c = Color::FromHSV(120.0f, 1.0f, 1.0f);
        CHECK(c.R8() == 0);
        CHECK(c.G8() == 255);
        CHECK(c.B8() == 0);
    }
    SUBCASE("blue H=240")
    {
        Color c = Color::FromHSV(240.0f, 1.0f, 1.0f);
        CHECK(c.R8() == 0);
        CHECK(c.G8() == 0);
        CHECK(c.B8() == 255);
    }
    SUBCASE("yellow H=60")
    {
        Color c = Color::FromHSV(60.0f, 1.0f, 1.0f);
        CHECK(c.R8() == 255);
        CHECK(c.G8() == 255);
        CHECK(c.B8() == 0);
    }
}

TEST_CASE("Color - FromHSV white and black")
{
    SUBCASE("white: zero saturation, full value")
    {
        Color c = Color::FromHSV(0.0f, 0.0f, 1.0f);
        CHECK(c.R8() == 255);
        CHECK(c.G8() == 255);
        CHECK(c.B8() == 255);
    }
    SUBCASE("black: zero value")
    {
        Color c = Color::FromHSV(0.0f, 1.0f, 0.0f);
        CHECK(c.R8() == 0);
        CHECK(c.G8() == 0);
        CHECK(c.B8() == 0);
    }
}

TEST_CASE("Color - FromHSV hue wrapping")
{
    SUBCASE("H=360 wraps to red")
    {
        Color c = Color::FromHSV(360.0f, 1.0f, 1.0f);
        CHECK(c.R8() == 255);
        CHECK(c.G8() == 0);
        CHECK(c.B8() == 0);
    }
    SUBCASE("negative hue wraps correctly")
    {
        Color neg = Color::FromHSV(-120.0f, 1.0f, 1.0f);
        Color pos = Color::FromHSV(240.0f,  1.0f, 1.0f);
        CHECK(neg.R8() == pos.R8());
        CHECK(neg.G8() == pos.G8());
        CHECK(neg.B8() == pos.B8());
    }
}

TEST_CASE("Color - FromHSV preserves full alpha")
{
    Color c = Color::FromHSV(0.0f, 1.0f, 1.0f);
    CHECK(c.A8() == 255);
}
