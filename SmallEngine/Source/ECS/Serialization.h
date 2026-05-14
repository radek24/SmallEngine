//
// Created by radov on 03.05.2026.
//


#pragma once

#include "Components/TransformComponent.h"
#include "json/json.hpp"

template<typename T>
struct ComponentSerializer {
    static void Save(const T& comp, nlohmann::json& out);
    static T Load(const nlohmann::json& in);
};
/*
template<>
struct ComponentSerializer<TransformComponent> {
    static constexpr const char* TypeName = "TransformComponent";
    static void Save(const TransformComponent& comp, nlohmann::json& out)
    {
        out["x"] = comp.Position.X;
        out["y"] = comp.Position.Y;
        out["sx"] = comp.Scale.X;
        out["sy"] = comp.Scale.Y;
        out["rot"] = comp.Rotation.GetAngleDegrees();
    }

    static TransformComponent Load(const nlohmann::json& in)
    {
        return { {in["x"], in["y"]}, {in["sx"], in["sy"]}, in["rot"] };
    }
};
*/