//
// Created by radov on 17.04.2026.
//


#pragma once

/** Enum used to differentiate between system types and between when they are run*/
enum class SystemPhase
{
    Update,
    Physics,
    Render
};

class Registry;

/** Base class for any system which will operate on components.*/
class System {
public:
    virtual ~System() = default;
    virtual void Update(Registry& CurrentRegistry, float DeltaTime) = 0;
    [[nodiscard]] virtual SystemPhase GetPhase() const = 0;
};