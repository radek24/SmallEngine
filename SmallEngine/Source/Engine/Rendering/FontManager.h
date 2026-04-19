//
// Created by radov on 19.04.2026.
//


#pragma once
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>

using FontHandle = uint32_t;
static constexpr FontHandle INVALID_FONT = 0;

/** Class responsible for managing, loading and unloading fonts*/
class FontManager
{
    // TODO: Trosku moc structu ve tride na muj vkus
    struct FontKey
    {
        std::string Path;
        int         Size;
        bool operator==(const FontKey& Other) const
        {
            return Path == Other.Path && Size == Other.Size;
        }
    };

    struct FontKeyHash
    {
        size_t operator()(const FontKey& K) const
        {
            return std::hash<std::string>{}(K.Path) ^ std::hash<int>{}(K.Size);
        }
    };

    std::unordered_map<FontKey, FontHandle, FontKeyHash> KeyToHandle;
    std::unordered_map<FontHandle, TTF_Font*>            HandleToFont;
    FontHandle NextHandle = 1;
public:
    FontManager();
    ~FontManager();
    /** Loads or gets already loaded font*/
    FontHandle Load(const std::string& Path, int Size);
    /** Gets native font from handle*/
    [[nodiscard]] TTF_Font* Get(FontHandle Handle) const;

};
