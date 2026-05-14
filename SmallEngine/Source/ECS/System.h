//
// Created by radov on 17.04.2026.
//


#pragma once
#include "Entity.h"

/** Enum used to differentiate between system types and between when they are run*/
enum class SystemPhase
{
    Update,
    Physics,
    PostUpdate,
    Render,
    RenderUI
};

class Registry;
/** Base class for any system which will operate on components.*/
class System {
public:
    virtual ~System() = default;
    /** Called every frame if registered*/
    virtual void Update(Registry& CurrentRegistry, float DeltaTime) = 0;
    /** Returns the phase in which we will update this system, override this on every system you create. */
    [[nodiscard]] virtual SystemPhase GetPhase() const = 0;
    /** Callback for on destruction of any entity, so system can cleanup*/
    virtual void OnEntityDestroyed(Entity E){};
};