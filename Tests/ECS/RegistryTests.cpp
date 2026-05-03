#include <doctest/doctest.h>
#include <ECS/Registry.h>
#include "Engine/Math/MathForward.h"


TEST_CASE("Regisry - Create Entity")
{
    Registry r;
    Entity e = r.CreateEntity();
    CHECK(e.GetId() == 1);
}

TEST_CASE("Regisry - Create Entity, unique IDS")
{
    Registry r;
    Entity e = r.CreateEntity();
    Entity e1 = r.CreateEntity();
    CHECK(e != e1);
}

TEST_CASE("Registry - Check if entity is valid ")
{
    Registry r;
    Entity e  = r.CreateEntity();
    CHECK(r.IsValid(e));
    r.DestroyEntity(e);
    CHECK(!r.IsValid(e));
}

TEST_CASE("Registry - Destroying Entity")
{
    Registry r;
    Entity e  = r.CreateEntity();
    CHECK(r.DestroyEntity(e));
    CHECK(!r.DestroyEntity(e));
}
TEST_CASE("Registry - Removing entity with active components")
{
    Registry r;
    Entity e  = r.CreateEntity();
    r.AddComponent<int>(e,10);
    r.AddComponent<Vector2f>(e, 1.0f, 1.0f);
    CHECK(r.Get<int>(e) == 10);
    r.DestroyEntity(e);
    CHECK(!r.IsValid(e));
    CHECK(r.GetPool<int>().Size() == 0);
    CHECK(r.GetPool<Vector2f>().Size() == 0);
    CHECK(!r.GetPool<int>().Contains(e));
    CHECK(!r.GetPool<Vector2f>().Contains(e));
}

class TestSystem : public System
{
public:
    void Update(Registry &CurrentRegistry, float DeltaTime) override
    {
        auto Callback = [DeltaTime](Entity E, int &num)
        {
            num += 1;
        };
        CurrentRegistry.MakeView<int>().Each(Callback);
    }
    [[nodiscard]] SystemPhase GetPhase() const override{return SystemPhase::Update;}
};

TEST_CASE("Registry - Add and Remove systems")
{
    Registry r;
    CHECK(!r.HasSystem<TestSystem>());
    r.AddSystem<TestSystem>();
    CHECK(r.HasSystem<TestSystem>());
    r.RemoveSystem<TestSystem>();
    CHECK(!r.HasSystem<TestSystem>());
}

TEST_CASE("Registry - Running simple system")
{
    Registry r;
    r.AddSystem<TestSystem>();
    Entity e  = r.CreateEntity();
    r.AddComponent<int>(e,10);
    r.RunSystems(SystemPhase::Update,0.0f);
    CHECK(r.Get<int>(e) == 11);
    r.RunSystems(SystemPhase::Render,0.0f);
    CHECK(r.Get<int>(e) == 11);
}

TEST_CASE("Registry - Generation divide")
{
    Registry r;
    Entity old = r.CreateEntity();
    r.DestroyEntity(old);
    Entity fresh = r.CreateEntity();
    CHECK_FALSE(r.IsValid(old));
    CHECK(r.IsValid(fresh));
}
