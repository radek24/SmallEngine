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
    InternalRenderer = window.ConstructRenderer();
    SDL_SetRenderVSync(InternalRenderer, 1);
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
    SDL_SetRenderDrawBlendMode(InternalRenderer, SDL_BLENDMODE_BLEND);
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

void Renderer::DrawRectangleBorders(const Vector2f &LeftTopCorner, const Vector2f &Size, const Color &LineColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(LineColor));
    const SDL_FRect Rect = {LeftTopCorner.X,LeftTopCorner.Y,Size.X,Size.Y};
    SDL_RenderRect(InternalRenderer,&Rect);
}

void Renderer::DrawFilledCircle(const Vector2f &Pos, float Radius, const Color &PointColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(PointColor));
    for (int y = -Radius; y <= Radius; y++)
    {
        int dx = (int)SDL_sqrt((double)(Radius * Radius - y * y));
        SDL_RenderLine(InternalRenderer, Pos.X - dx, Pos.Y + y, Pos.X + dx, Pos.Y + y);
    }
}

void Renderer::DrawTexture(const Vector2f &Pos,const Rotator& Rot, const Vector2f &Size, SDL_Texture *Texture) const
{
    const SDL_FRect rect = { Pos.X, Pos.Y, Size.X, Size.Y };
    SDL_RenderTextureRotated(InternalRenderer,Texture,nullptr,&rect,Rot.GetAngleDegrees(),nullptr,SDL_FLIP_NONE);
}

void Renderer::DrawTextureTinted(const Vector2f &Pos,const Rotator& Rot, const Vector2f &Size, SDL_Texture *Texture,const Color &Tint) const
{
    SDL_SetTextureColorModFloat(Texture, Tint.RF(), Tint.GF(), Tint.BF());
    DrawTexture(Pos,Rot,Size,Texture);
    SDL_SetTextureColorModFloat(Texture, 1.0f, 1.0f, 1.0f);
}

void Renderer::DrawDebugText(const Vector2f &Pos, const char *s, const Color &TextColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(TextColor));
    SDL_RenderDebugText(InternalRenderer,Pos.X,Pos.Y,s);
}

void Renderer::DrawLine(const Vector2f &StartPos, const Vector2f &EndPos, float Thickness, const Color &LineColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(LineColor));
    SDL_RenderLine(InternalRenderer,StartPos.X, StartPos.Y, EndPos.X, EndPos.Y);
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
    auto T = IMG_LoadTexture(InternalRenderer, Path.c_str());
    if (T)
        SDL_SetTextureScaleMode(T, SDL_SCALEMODE_LINEAR);
    return T;
}
