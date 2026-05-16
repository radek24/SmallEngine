#pragma once

struct AsteroidComponent
{
    int Tier = 3;
    float Radius = 46.0f;

    static float RadiusForTier(int Tier)
    {
        if (Tier == 3) return 46.0f;
        if (Tier == 2) return 26.0f;
        return 14.0f;
    }

    static AsteroidComponent FromTier(int Tier)
    {
        return AsteroidComponent{Tier, RadiusForTier(Tier)};
    }
};