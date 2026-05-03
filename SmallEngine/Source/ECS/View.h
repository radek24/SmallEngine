//
// Created by radov on 17.04.2026.
//

#pragma once
#include <tuple>
#include "ComponentPool.h"
#include "Entity.h"


/** Class used to iterate over entities with excact component combinantion. */
template<typename... Components>
class View {
    std::tuple<ComponentPool<Components>*...> Pools;

public:
    explicit View(ComponentPool<Components>&... InPools) : Pools(&InPools...) {}

    /** Iterate over entities with components, Each callback will receive Entity and components.*/
    template<typename Func>
    void Each(Func&& Callback) {
        auto* FirstPool = std::get<0>(Pools);
        for (auto [E, Ignored] : *FirstPool) {
            if (ContainsInAll(E))
                Callback(E, std::get<ComponentPool<Components>*>(Pools)->Get(E)...);
        }
    }

private:
    [[nodiscard]] bool ContainsInAll(Entity E) const
    {
        return (std::get<ComponentPool<Components>*>(Pools)->Contains(E) && ...);
    }
};
