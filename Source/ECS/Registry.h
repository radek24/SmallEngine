//
// Created by radov on 08.03.2026.
//

#pragma once
#include "Entity.h"

/** Represents one level with all entities, components and systems needed */
class Registry {
public:
    Registry();
    [[nodiscard]] Entity CreateEntity();
    bool DestroyEntity(const Entity& E);
template <typename T>
    void AddComponent<T>();

public:
    Entity::IdType CurrentID;

};



