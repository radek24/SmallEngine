//
// Created by radov on 03.05.2026.
//


#pragma once
#include "Engine/Level.h"


class SimpleTestSaveLevel :public Level
{
public:
    void OnEnter() override;
    void OnUpdate(float DeltaTime) override;
};
