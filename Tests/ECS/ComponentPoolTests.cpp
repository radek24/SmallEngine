#include <doctest/doctest.h>
#include <ECS/ComponentPool.h>
#include <ECS/Entity.h>
#include <ECS/Registry.h>


TEST_CASE("ComponentPool - add and retrieve")
{
    Registry r;
    auto e = r.CreateEntity();
    r.AddComponent<int>(e,64);
    REQUIRE(r.GetPool<int>().Contains(e));
    CHECK_EQ(r.Get<int>(e), 64);
}

TEST_CASE("ComponentPool - size")
{
    Registry r;
    for (int i = 0; i < 100000; ++i)
    {
        Entity e = r.CreateEntity();
        r.AddComponent<int>(e,i);
    }
    CHECK_EQ(r.GetPool<int>().Size(), 100000);
}
TEST_CASE("ComponentPool - reserve")
{
    Registry r;
    r.GetPool<int>().Reserve(100);
    REQUIRE(r.GetPool<int>().Size() == 0 );
}
TEST_CASE("ComponentPool - removing entities")
{
    Registry r;
    Entity e1 = r.CreateEntity();
    Entity e2 = r.CreateEntity();
    r.AddComponent<int>(e1);
    r.AddComponent<int>(e2);
    r.GetPool<int>().Remove(e1);
    REQUIRE(!r.GetPool<int>().Contains(e1));
    REQUIRE(r.GetPool<int>().Contains(e2));
}

