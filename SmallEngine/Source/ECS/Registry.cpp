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
    if(CurrentID == UINT32_MAX)
        LOG_FATAL("Reached max entity ids");
    CurrentID++;
    return Entity(CurrentID);
}

bool Registry::DestroyEntity(Entity E)
{
    Unimplemented();
    return false;
}

bool Registry::IsValid(Entity E)
{
    return true;
}

void Registry::RunSystems(SystemPhase Phase, float DeltaTime)
{
    for (auto& S : Systems)
        if (S->GetPhase() == Phase)
            S->Update(*this, DeltaTime);
}
