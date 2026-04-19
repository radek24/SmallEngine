//
// Created by radov on 08.03.2026.
//

#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "ComponentPool.h"
#include "Entity.h"
#include "System.h"
#include "View.h"

/** Simple struct used for tracking entities */
struct EntitySlot { Entity::IdType GeneratedID; bool Alive; };

/** Represents one level with all entities, components and systems needed */
class Registry
{
public:
    Registry();
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
    //TODO: Check if system is already added;
    static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
    auto& Ref = Systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return static_cast<T&>(*Ref);
}

template<typename T, typename... Args>
T& Registry::AddComponent(Entity E, Args&&... args) {
    assert(IsValid(E) && "Adding component on destroyed entity");
    return GetPool<T>().Add(E, T{ std::forward<Args>(args)... });
}