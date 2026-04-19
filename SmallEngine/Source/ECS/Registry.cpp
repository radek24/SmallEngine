//
// Created by radov on 08.03.2026.
//

#include "Registry.h"

#include "Engine/DebugBreaks.h"

Registry::Registry()
{
    CurrentID = 0;
}

Entity Registry::CreateEntity()
{
    if (!FreeList.empty()) {
        Entity::IdType Idx = FreeList.back();
        FreeList.pop_back();
        Slots[Idx].Alive = true;
        return Entity((static_cast<Entity::IdType>(Slots[Idx].Generation) << 24) | Idx);
    }

    auto Idx = static_cast<Entity::IdType>(Slots.size());
    if (Idx >= 0x00FFFFFF)
        LOG_FATAL("Reached max entity ids");

    Slots.push_back({ 0, true });
    return Entity(Idx);
}

bool Registry::DestroyEntity(Entity E)
{
    if (!IsValid(E))
        return false;

    for (auto& S : Systems)
        S->OnEntityDestroyed(E);

    for (auto& [Type, Pool] : Pools)
        Pool->Remove(E);

    Entity::IdType Idx = E.GetId() & 0x00FFFFFF;
    Slots[Idx].Alive = false;
    Slots[Idx].Generation++;

    FreeList.push_back(Idx);
    return true;
}

bool Registry::IsValid(Entity E)
{
    Entity::IdType Idx = E.GetId() & 0x00FFFFFF;
    if (Idx >= Slots.size())
        return false;

    auto Gen = static_cast<uint8_t>(E.GetId() >> 24);
    return Slots[Idx].Alive && Slots[Idx].Generation == Gen;
}

void Registry::RunSystems(SystemPhase Phase, float DeltaTime)
{
    for (auto& S : Systems)
        if (S->GetPhase() == Phase)
            S->Update(*this, DeltaTime);
}
