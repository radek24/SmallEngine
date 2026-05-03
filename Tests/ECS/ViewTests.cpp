//
// Created by radov on 01.05.2026.
//
#include <doctest/doctest.h>
#include <ECS/Registry.h>
#include "Engine/Math/MathForward.h"

TEST_CASE("View - Get correct entities")
{
    Registry r;
    Entity e  = r.CreateEntity();
    r.AddComponent<int>(e,10);
    r.AddComponent<Vector2f>(e, 1.0f, 1.0f);
    Entity e2 = r.CreateEntity();
    Entity e3 = r.CreateEntity();
    r.AddComponent<Vector2f>(e3, 2.0f, 2.0f);
    r.AddComponent<int>(e2,12);


    std::vector<int> Out;
    auto Callback = [&Out](Entity E, int &T)
    {
        Out.push_back(T);
    };
    r.MakeView<int>().Each(Callback);
    CHECK(std::find(Out.begin(), Out.end(), 10) != Out.end());
    CHECK(std::find(Out.begin(), Out.end(), 12) != Out.end());
    CHECK(Out.size() == 2);

    std::vector<Vector2f> Out2;
    auto Callback2 = [&Out2](Entity E, int &T,Vector2f &V)
    {
        Out2.push_back(V);
    };
    r.MakeView<int,Vector2f>().Each(Callback2);
    auto v = Vector2f(1.0,1.0);
    CHECK(std::find(Out2.begin(), Out2.end(), v) != Out2.end());
    CHECK(Out2.size() == 1);

}