//
// Created by radov on 22.04.2026.
//


#pragma once


/** Component used to modify sounds played on entity. Isn't mandatory for sounds to play*/
struct AudioConfigComponent
{
    float Volume = 1.0f;
    float Pitch = 1.0f;
    bool Muted = false;
};
