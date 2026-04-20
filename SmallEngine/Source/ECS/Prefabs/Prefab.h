//
// Created by radov on 20.04.2026.
//


#pragma once
#include <functional>
#include <string>
#include <vector>
#include <ECS/Registry.h>

#include "ECS/ComponentUtils.h"

/** Type erased Component initializer*/
struct ComponentInitializer
{
    ComponentTypeID TypeID;
    std::function<void(Entity, Registry&)> Apply;
};

/** Used to store entity with components for easy reusability*/
struct Prefab
{
    std::string Name;
    std::vector<ComponentInitializer> Components;

    template<typename T>
    Prefab& Add(T componentData);

    Entity Instantiate(Registry& reg) const
    {
        Entity e = reg.CreateEntity();
        for (auto& comp : Components)
            comp.Apply(e, reg);
        return e;
    }
};

template<typename T>
Prefab & Prefab::Add(T componentData)
{
    Components.push_back(
{
    ComponentUtils::GetComponentTypeID<T>(),
    [componentData](Entity e, Registry& reg)
    {
        reg.AddComponent<T>(e, componentData);
    }
    });
    return *this;
}

