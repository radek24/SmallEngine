//
// Created by radov on 18.03.2026.
//


#pragma once
#include "Engine/Level.h"

class TestLevel : public Level
{
    public:
        void OnEnter() override;

        void OnUpdate(float DeltaTime) override;

        void OnRender(const Renderer &Renderer) override;

        void OnExit() override;
};
