//
// Created by Radovan Šťastný on 20.03.2026.
//

#pragma once
#include "Engine/Level.h"


class SecondLevel final : public Level
{
public:
    void OnEnter() override;

    void OnUpdate(float DeltaTime) override;

    void OnRender(const Renderer &Renderer) override;

    void OnExit() override;
};
