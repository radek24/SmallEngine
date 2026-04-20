//
// Created by radov on 08.03.2026.
//

#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

#include <Engine/Core.h>
#include "ComponentPool.h"
#include "Entity.h"
#include "System.h"
#include "View.h"

/** Simple struct used for tracking entities */
struct EntitySlot
{
    uint8_t Generation = 0;
    bool Alive = false;
};

/** Represents one level with all entities, components and systems needed */
class SE_API Registry
{
public:
    Registry();
    Registry(const Registry&) = delete;
    Registry& operator=(const Registry&) = delete;
    Registry(Registry&&) = default;
    Registry& operator=(Registry&&) = default;
    [[nodiscard]] Entity CreateEntity();
    bool DestroyEntity(Entity E);
    /**Checks whether the entity is destroyed or is alive*/
    [[nodiscard]] bool IsValid(Entity E);
    /** Used to get or create pool of certain components*/
    template<typename T>
    ComponentPool<T>& GetPool();
    /** Get view with specific components.*/
    template<typename... Components>
    View<Components...> MakeView();
    /** Adds system to a registry, currently doesn't check if the system is already added*/
    template<typename T, typename... Args>
    T& AddSystem(Args&&... args);
    /** Removes a system from a registry */
    template<typename T>
    void RemoveSystem();
    /** Checks if there is this system in this registry */
    template<typename T>
    bool HasSystem() const;


    /** Runs all systems of a certain type*/
    void RunSystems(SystemPhase Phase, float DeltaTime);
    /** Adds a component to a specific entity*/
    template<typename T, typename... Args>
    T& AddComponent(Entity E, Args&&... args);

public:
    Entity::IdType CurrentID;
    std::vector<std::unique_ptr<System>> Systems;
private:
    std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> Pools;
    std::vector<EntitySlot> Slots;
    std::vector<Entity::IdType> FreeList;
};

template<typename T>
ComponentPool<T>& Registry::GetPool() {
    auto ID = std::type_index(typeid(T));
    if (!Pools.count(ID))
        Pools[ID] = std::make_unique<ComponentPool<T>>();
    return static_cast<ComponentPool<T>&>(*Pools[ID]);
}

template<typename... Components>
View<Components...> Registry::MakeView()
{
    return View<Components...>(GetPool<Components>()...);
}

template<typename T, typename... Args>
T& Registry::AddSystem(Args&&... args)
{
    if (HasSystem<T>())
        LOG_WARN("System already added to registry");
    static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
    auto& Ref = Systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return static_cast<T&>(*Ref);
}

template<typename T>
void Registry::RemoveSystem()
{
    static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
    std::erase_if(Systems, [](const auto& S)
    {
        return dynamic_cast<T*>(S.get()) != nullptr;
    });
}

template<typename T>
bool Registry::HasSystem() const
{
    static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
    for (auto& S : Systems)
    {
        if (dynamic_cast<T*>(S.get()) != nullptr)
            return true;
    }
    return false;
}

template<typename T, typename... Args>
T& Registry::AddComponent(Entity E, Args&&... args) {
    Assert(IsValid(E) && "Adding component on destroyed entity");
    return GetPool<T>().Add(E, T{ std::forward<Args>(args)... });
}
