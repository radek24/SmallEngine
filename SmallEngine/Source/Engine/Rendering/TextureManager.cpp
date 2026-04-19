//
// Created by radov on 19.04.2026.
//

#include "TextureManager.h"

#include <Engine/DebugBreaks.h>

TextureManager::~TextureManager()
{
    for (auto& [Handle, Tex] : HandleToTexture)
        SDL_DestroyTexture(Tex);
}

TextureHandle TextureManager::LoadTexture(const std::string& Path)
{
    if (PathToHandleMap.contains(Path))
        return PathToHandleMap[Path];

    SDL_Texture* Tex = CurrentRenderer->LoadTexture(Path);
    if(!Tex)
        LOG_ERROR("Failed to load texture");

    LOG_INFO("Loaded texture {0}", Path);
    TextureHandle Handle = NextHandle++;
    PathToHandleMap[Path] = Handle;
    HandleToTexture[Handle] = Tex;
    float w,h;
    SDL_GetTextureSize(Tex,&w,&h);
    HandleToSize[Handle] = Vector2f(w,h);

    return Handle;
}

SDL_Texture * TextureManager::Get(TextureHandle Handle)
{
    auto It = HandleToTexture.find(Handle);
    return It != HandleToTexture.end() ? It->second : nullptr;
}

Vector2f TextureManager::GetSize(TextureHandle Handle)
{
    auto It = HandleToSize.find(Handle);
    return It != HandleToSize.end() ? It->second : Vector2f{0, 0};
}
