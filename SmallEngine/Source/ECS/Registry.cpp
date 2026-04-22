//
// Created by radov on 08.03.2026.
//

#include "Registry.h"

#include "Engine/DebugBreaks.h"
#include "SDL3/SDL_timer.h"

Registry::Registry()
{
    CurrentID = 0;
}

void Registry::ReserveEntities(size_t Count)
{
    Slots.reserve(Slots.size() + Count);
    FreeList.reserve(Count);
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

// Anonymous function, kinda bad
static std::string GetCleanTypeName(const std::type_info& type)
{
    std::string name = type.name();
    for (auto& prefix : {"class ", "struct "})
    {
        size_t pos = name.find(prefix);
        if (pos != std::string::npos)
            name.erase(pos, strlen(prefix));
    }
    return name;
}

void Registry::RunSystems(SystemPhase Phase, float DeltaTime)
{
    for (auto& S : Systems)
        if (S->GetPhase() == Phase)
        {
            #ifdef SE_DEBUG
            auto start = SDL_GetPerformanceCounter();
            #endif
            S->Update(*this, DeltaTime);
            #ifdef SE_DEBUG
            auto elapsed = (SDL_GetPerformanceCounter() - start) * 1000.0 / SDL_GetPerformanceFrequency();
            CurrentTimings.push_back({GetCleanTypeName(typeid(*S)),elapsed});
            #endif
        }
}

#ifdef SE_DEBUG
size_t Registry::GetNumberOfEntities() const
{
    size_t Count = 0;
    for(auto ES : Slots)
    {
        if(ES.Alive == true)
            Count++;
    }
    return Count;
}

size_t Registry::GetNumberOfSystems() const
{
    return Systems.size();
}

std::vector<SystemTiming>& Registry::GetTimings()
{
    return LastFrameTimings;
}

void Registry::FlushTimings()
{
    LastFrameTimings.clear();
    LastFrameTimings = CurrentTimings;
    CurrentTimings.clear();
}
#endif
