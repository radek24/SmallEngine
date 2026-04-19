//
// Created by radov on 19.04.2026.
//

#include "FontManager.h"

#include <Engine/Log/Log.h>

FontManager::FontManager()
{
    TTF_Init();
}

FontManager::~FontManager()
{
    for (auto& [Handle, Font] : HandleToFont)
        TTF_CloseFont(Font);
    TTF_Quit();
}

FontHandle FontManager::Load(const std::string &Path, int Size)
{
    FontKey Key{ Path, Size };
    if (KeyToHandle.contains(Key))
        return KeyToHandle[Key];

    TTF_Font* Font = TTF_OpenFont(Path.c_str(), Size);
    if(!Font)
        LOG_FATAL("Failed to load font {0}", Path);

    LOG_INFO("Loaded font {0}",Path);
    FontHandle Handle = NextHandle++;
    KeyToHandle[Key] = Handle;
    HandleToFont[Handle] = Font;
    return Handle;
}

TTF_Font * FontManager::Get(FontHandle Handle) const
{
    auto It = HandleToFont.find(Handle);
    return It != HandleToFont.end() ? It->second : nullptr;
}
