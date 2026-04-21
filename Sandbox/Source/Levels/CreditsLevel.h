//
// Created by Radovan Šťastný on 21.04.2026.
//

#pragma once
#include "Engine/Level.h"


class CreditsLevel :public Level
{
public:
    void OnEnter() override;
    std::vector<std::string> Credits ={"This game and engine", "was created for CPP course","By Radovan Stastny", " ","Technology used:", "SDL3, SDL Image and SDL TTF", "SpdLog"};
};
