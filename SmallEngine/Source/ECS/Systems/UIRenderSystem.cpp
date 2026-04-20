//
// Created by radov on 19.04.2026.
//

#include "UIRenderSystem.h"

#include <ECS/Registry.h>

#include "ECS/Components/UITextComponent.h"
#include "ECS/Components/TransformComponent.h"

UIRenderSystem::~UIRenderSystem()
{
    for (auto& [E, C] : Cache)
        if (C.Texture) SDL_DestroyTexture(C.Texture);
}

void UIRenderSystem::Update(Registry &CurrentRegistry, float DeltaTime)
{
    auto FontRenderCallback = [&](Entity E, UITextComponent& TC, TransformComponent& T)
    {
        if (!TC.Visible || TC.Text.empty()) return;
        auto& Cached = Cache[E];
        bool Dirty = Cached.LastText     != TC.Text
                  || Cached.LastSize     != TC.FontSize
                  || Cached.LastColor.r  != TC.FontColor.R8()
                  || Cached.LastColor.g  != TC.FontColor.G8()
                  || Cached.LastColor.b  != TC.FontColor.B8()
                  || Cached.LastColor.a  != TC.FontColor.A8();

        if (Dirty)
        {
            if (Cached.Texture)
                SDL_DestroyTexture(Cached.Texture);

            TTF_Font* Font = Fonts.Get(Fonts.Load(TC.FontPath, TC.FontSize));
            SDL_Surface* Surface = TTF_RenderText_Blended(Font, TC.Text.c_str(), TC.Text.size(), TC.FontColor.GetSDLColor());
            Cached.Texture = RendererRef->CreateTextureFromSurface(Surface);
            SDL_DestroySurface(Surface);

            Cached.LastText  = TC.Text;
            Cached.LastSize  = TC.FontSize;
            Cached.LastColor = TC.FontColor.GetSDLColor();
        }

        if (!Cached.Texture)
            return;

        float W, H;
        SDL_GetTextureSize(Cached.Texture, &W, &H);
        Vector2f TextureSize(W,H);
        RendererRef->DrawTexture(T.Transform.Position,T.Transform.Rotation,TextureSize*T.Transform.Scale,Cached.Texture);
    };

    CurrentRegistry.MakeView<UITextComponent, TransformComponent>().Each(FontRenderCallback);

}

void UIRenderSystem::OnEntityDestroyed(Entity E)
{
    auto It = Cache.find(E);
    if (It != Cache.end()) {
        if (It->second.Texture)
            SDL_DestroyTexture(It->second.Texture);
        Cache.erase(It);
    }
}
