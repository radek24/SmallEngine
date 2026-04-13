//
// Created by radov on 09.03.2026.
//

#include "Renderer.h"

#include <Engine/Log/Log.h>
#include <SDL3/SDL.h>

std::unique_ptr<Renderer> Renderer::Create(const Window &window)
{
    return std::make_unique<Renderer>(window);
}

Renderer::Renderer(const Window &window)
{
    InternalRenderer = SDL_CreateRenderer(window.GetNativeHandle(), nullptr);
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

void Renderer::DrawTexture(const Vector2f &Pos, const Vector2f &Size, SDL_Texture *Texture) const
{
    const SDL_FRect rect = { Pos.X, Pos.Y, Size.X, Size.Y };
    SDL_RenderTexture(InternalRenderer, Texture, nullptr, &rect);
}

void Renderer::DrawDebugText(const Vector2f &Pos, const char *s, const Color &TextColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, COLOR_TO_SDL(TextColor));
    SDL_RenderDebugText(InternalRenderer,Pos.X,Pos.Y,s);
}

void Renderer::SetClearColor(const Color &ClearColor)
{
    this->ClearColor = ClearColor;
}