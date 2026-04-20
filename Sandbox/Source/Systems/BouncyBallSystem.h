//
// Created by radov on 20.04.2026.
//


#pragma once
#include <Engine/Rendering/Renderer.h>
#include <Engine/Rendering/Window.h>

#include "ECS/System.h"


class BouncyBallSystem : public System
{
public:
    BouncyBallSystem(Window* CurrentWindow): CurrentWindow(CurrentWindow){};
    void Update(Registry &CurrentRegistry, float DeltaTime) override;

    [[nodiscard]] SystemPhase GetPhase() const override {return SystemPhase::Physics;}

    Window* CurrentWindow;
};
