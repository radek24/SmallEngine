//
// Created by radov on 09.03.2026.
//

#include "Renderer.h"

#include <Engine/Log/Log.h>
#include <SDL3/SDL.h>
#include <SDL_image/include/SDL3_image/SDL_image.h>

std::unique_ptr<Renderer> Renderer::Create(Window &window)
{
    return std::make_unique<Renderer>(window);
}

Renderer::Renderer(Window &window)
{
    InternalRenderer = SDL_CreateRenderer(window.GetNativeHandle(), nullptr);
    SDL_RendererLogicalPresentation Presentation = SDL_LOGICAL_PRESENTATION_DISABLED;
    switch (window.GetSpecs().Presentation)
    {
        case LogicalPresentation::Letterbox: Presentation = SDL_LOGICAL_PRESENTATION_LETTERBOX; break;
        case LogicalPresentation::Stretch: Presentation = SDL_LOGICAL_PRESENTATION_STRETCH; break;
        case LogicalPresentation::OverScan: Presentation = SDL_LOGICAL_PRESENTATION_OVERSCAN; break;
        case LogicalPresentation::Disabled: Presentation = SDL_LOGICAL_PRESENTATION_DISABLED; break;
        default: NoEntry() break;
    }
    SDL_SetRenderLogicalPresentation(InternalRenderer,window.GetWidth(), window.GetHeight(), Presentation);
}

Renderer::~Renderer()
{
    LOG_INFO("Destroying Renderer");
    SDL_DestroyRenderer(InternalRenderer);
    LOG_INFO("Renderer Destructed");
}

void Renderer::BeginFrame() const
{
    Clear();
}

void Renderer::EndFrame() const
{
    SDL_RenderPresent(InternalRenderer);
}

void Renderer::Clear() const
{

    SDL_SetRenderDrawColor(InternalRenderer,COLOR_TO_SDL(ClearColor));
    SDL_RenderClear(InternalRenderer);
}

void Renderer::DrawRectangle(const Vector2f& Pos, const Vector2f &Size, const Color &ShapeColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(ShapeColor));
    SDL_FRect rect = { Pos.X, Pos.Y, Size.X, Size.Y };
    SDL_RenderFillRect(InternalRenderer, &rect);
}

void Renderer::DrawPoint(const Vector2f &Pos, float Radius, const Color &PointColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(PointColor));
    SDL_RenderPoint(InternalRenderer,Pos.X,Pos.Y);
}

void Renderer::DrawTexture(const Vector2f &Pos,const Rotator& Rot, const Vector2f &Size, SDL_Texture *Texture) const
{
    const SDL_FRect rect = { Pos.X, Pos.Y, Size.X, Size.Y };
    SDL_RenderTexture(InternalRenderer, Texture, nullptr, &rect);
    SDL_RenderTextureRotated(InternalRenderer,Texture,nullptr,&rect,Rot.GetAngleDegrees(),nullptr,SDL_FLIP_NONE);
}

void Renderer::DrawTextureTinted(const Vector2f &Pos,const Rotator& Rot, const Vector2f &Size, SDL_Texture *Texture,const Color &Tint) const
{
    SDL_SetTextureColorModFloat(Texture, Tint.RF(), Tint.GF(), Tint.BF());
    DrawTexture(Pos,Rot,Size,Texture);
}

void Renderer::DrawDebugText(const Vector2f &Pos, const char *s, const Color &TextColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(TextColor));
    SDL_RenderDebugText(InternalRenderer,Pos.X,Pos.Y,s);
}

SDL_Texture* Renderer::CreateTextureFromSurface( SDL_Surface *Surface)
{
    return SDL_CreateTextureFromSurface(InternalRenderer, Surface);
}

void Renderer::SetClearColor(const Color &ClearColor)
{
    this->ClearColor = ClearColor;
}

SDL_Texture * Renderer::LoadTexture(const std::string& Path) const
{
    return IMG_LoadTexture(InternalRenderer,Path.c_str());
}
