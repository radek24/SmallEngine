//
// Created by Radovan Šťastný on 21.04.2026.
//

#pragma once
#include <ECS/Entity.h>
#include <ECS/Registry.h>

#include "ECS/Components/TransformComponent.h"


class BackButtonPrefab {
    template <typename T>
    static Entity Create(Registry* R);
};

template<typename T>
Entity BackButtonPrefab::Create(Registry* R)
{
    auto E = R->CreateEntity();

}
