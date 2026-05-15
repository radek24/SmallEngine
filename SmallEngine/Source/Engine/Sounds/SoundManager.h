//
// Created by radov on 22.04.2026.
//


#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

#include "Engine/Core.h"
#include <SDL3_mixer/SDL_mixer.h>

using SoundHandle = uint32_t;
static constexpr SoundHandle INVALID_SOUND = 0;

class SE_API SoundManager
{
private:
    std::unordered_map<std::string, SoundHandle> PathToHandleMap;
    std::unordered_map<SoundHandle, MIX_Audio*>  HandleToAudio;
    SoundHandle NextHandle = 1;
    MIX_Mixer* Mixer = nullptr;
public:
    SoundManager();
    ~SoundManager();

    /** Loads or gets already loaded sound, returns handle */
    SoundHandle Load(const std::string& Path);
    /** Plays a fire-and-forget sound by handle */
    void Play(SoundHandle Handle);
    /** Plays a fire-and-forget sound by path, loading it if necessary */
    void Play(const std::string& Path);
    /** Sets master volume. 0.0 = silence, 1.0 = normal, >1.0 = louder */
    void SetVolume(float Volume);
    [[nodiscard]] float GetVolume() const;
};