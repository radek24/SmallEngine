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
    CurrentID++;
    return Entity(CurrentID);
}

bool Registry::DestroyEntity(const Entity &E) {
    Unimplemented();
    return false;
}
