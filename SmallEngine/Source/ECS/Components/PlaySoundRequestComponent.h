//
// Created by radov on 22.04.2026.
//


#pragma once
#include <string>

/** One-Frame component used to play sound on entity. */
struct PlaySoundRequestComponent
{
    std::string SoundPath;
    float Volume = 1.0f;
};
