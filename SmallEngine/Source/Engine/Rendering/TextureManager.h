//
// Created by radov on 19.04.2026.
//


#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

#include "Renderer.h"
#include "SDL3/SDL_render.h"

using TextureHandle = uint32_t;
static constexpr TextureHandle INVALID_TEXTURE = 0;

class SE_API TextureManager
{
private:
    std::unordered_map<std::string, TextureHandle> PathToHandleMap;
    std::unordered_map<TextureHandle, SDL_Texture*> HandleToTexture;
    std::unordered_map<TextureHandle, Vector2f> HandleToSize;

    TextureHandle NextHandle = 1;
    Renderer* CurrentRenderer = nullptr;
public:
    explicit TextureManager(Renderer* InRenderer): CurrentRenderer(InRenderer) {}
    ~TextureManager();

    /** Returns texture handle of suplied texture, user doesn't need to care if he already loaded or not, this is handled internally */
    TextureHandle LoadTexture(const std::string& Path);
    /** Returns SDL_Texture ref for this handle*/
    SDL_Texture* Get(TextureHandle Handle);
    /** Returns Native texture size for this handle*/
    Vector2f GetSize(TextureHandle Handle);

};
