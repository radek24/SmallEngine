//
// Created by radov on 09.03.2026.
//

#include "Renderer.h"

#include <Core/Log/Log.h>
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
    SDL_SetRenderDrawColor(InternalRenderer, 30, 30, 30, 255);
    SDL_RenderClear(InternalRenderer);
}

void Renderer::DrawRectangle(const Vector2f& Pos, const Vector2f &Size, const Color &ShapeColor) const
{
    SDL_SetRenderDrawColor(InternalRenderer, ShapeColor.NativeR(), ShapeColor.NativeG(), ShapeColor.NativeB(), ShapeColor.NativeA());
    SDL_FRect rect = { Pos.X, Pos.Y, Size.X, Size.Y };
    SDL_RenderFillRect(InternalRenderer, &rect);
}
