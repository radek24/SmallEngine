//
// Created by radov on 03.05.2026.
//


#pragma once

#include "Components/TransformComponent.h"
#include "Components/RotatorComponent.h"
#include "json/json.hpp"

template<typename T>
struct ComponentSerializer {
    static constexpr bool Serializable = false;
    static constexpr const char* TypeName = "";
};

template<>
struct ComponentSerializer<TransformComponent> {
    static constexpr bool Serializable = true;
    static constexpr const char* TypeName = "TransformComponent";

    static void Save(const TransformComponent& comp, nlohmann::json& out)
    {
        out["x"]   = comp.Position.X;
        out["y"]   = comp.Position.Y;
        out["sx"]  = comp.Scale.X;
        out["sy"]  = comp.Scale.Y;
        out["rot"] = comp.Rotation.GetAngleDegrees();
    }
};

template<>
struct ComponentSerializer<RotatorComponent> {
    static constexpr bool Serializable = true;
    static constexpr const char* TypeName = "RotatorComponent";

    static void Save(const RotatorComponent& comp, nlohmann::json& out)
    {
        out["speed"] = comp.RotationSpeed;
    }
};
