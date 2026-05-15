//
// Created by radov on 22.04.2026.
//

#include "SoundManager.h"

#include <Engine/Log/Log.h>
#include <SDL3/SDL_init.h>
#include <SDL3_mixer/SDL_mixer.h>

SoundManager::SoundManager()
{
    SDL_Init(SDL_INIT_AUDIO);
    MIX_Init();
    Mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    if (!Mixer)
        LOG_ERROR("Failed to create audio mixer: {0}", SDL_GetError());
}

SoundManager::~SoundManager()
{
    for (auto& [Handle, Audio] : HandleToAudio)
        MIX_DestroyAudio(Audio);
    MIX_DestroyMixer(Mixer);
    MIX_Quit();
}

SoundHandle SoundManager::Load(const std::string& Path)
{
    if (PathToHandleMap.contains(Path))
        return PathToHandleMap[Path];

    MIX_Audio* Audio = MIX_LoadAudio(Mixer, Path.c_str(), true);
    if (!Audio)
    {
        LOG_ERROR("Failed to load sound {0}: {1}", Path, SDL_GetError());
        return INVALID_SOUND;
    }

    LOG_INFO("Loaded sound {0}", Path);
    SoundHandle Handle = NextHandle++;
    PathToHandleMap[Path] = Handle;
    HandleToAudio[Handle] = Audio;
    return Handle;
}

void SoundManager::Play(SoundHandle Handle)
{
    auto It = HandleToAudio.find(Handle);
    if (It == HandleToAudio.end())
    {
        LOG_ERROR("SoundManager::Play called with invalid handle");
        return;
    }
    MIX_PlayAudio(Mixer, It->second);
}

void SoundManager::Play(const std::string& Path)
{
    Play(Load(Path));
}

void SoundManager::SetVolume(float Volume)
{
    MIX_SetMixerGain(Mixer, Volume);
}

float SoundManager::GetVolume() const
{
    return MIX_GetMixerGain(Mixer);
}