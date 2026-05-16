//
// Created by Radovan Šťastný on 09.03.2026.
//

#include "Window.h"

#include <SDL3_image/SDL_image.h>

#include "Engine/DebugBreaks.h"

std::unique_ptr<Window> Window::Create(const WindowSpecification &spec)
{
    return std::make_unique<Window>(spec);
}

Window::Window(const WindowSpecification &spec)
{
    Specs = spec;
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        LOG_ERROR("SDL_Init failed: {0}", SDL_GetError());
        return;
    }
    SDL_WindowFlags Flags = 0;
    if(spec.IsResizable)
        Flags = Flags | SDL_WINDOW_RESIZABLE;
    if(spec.IsBorderless)
        Flags = Flags | SDL_WINDOW_BORDERLESS;
    if(spec.IsFullscreen)
        Flags = Flags | SDL_WINDOW_FULLSCREEN;

    //Flags = Flags | SDL_WINDOW_HIGH_PIXEL_DENSITY;

    NativeHandle = SDL_CreateWindow(spec.Name.c_str(), spec.Size.X, spec.Size.Y, Flags);
    if(!NativeHandle)
    {
        LOG_ERROR("Window failed to create {0}",SDL_GetError());
        SDL_Quit();
    }
    SetupWindowIcon(spec);
}

Window::~Window()
{
    LOG_INFO("Destroying window...");
    SDL_DestroyWindow(NativeHandle);
    LOG_INFO("Window destroyed");

    LOG_INFO("Quiting SDL");
    SDL_Quit();
    LOG_INFO("SDL Quited sucesfully");
}

uint32_t Window::GetWidth() const
{
    int w,h;
    //SDL_GetWindowSizeInPixels(NativeHandle, &w, &h); //Might be useful for retina
    SDL_GetWindowSize(NativeHandle, &w, &h);
    return w;
}

uint32_t Window::GetHeight() const
{
    int w,h;
    SDL_GetWindowSize(NativeHandle, &w, &h);
    return h;
}

SDL_Renderer * Window::ConstructRenderer() const
{
    return SDL_CreateRenderer(NativeHandle, nullptr);
}

WindowSpecification Window::GetSpecs()
{
    return Specs;
}

void Window::SetupWindowIcon(const WindowSpecification& spec) const
{
    if(spec.WindowIcon.empty())
        return;

    SDL_Surface* Icon = IMG_Load(spec.WindowIcon.c_str());
    if (!Icon)
    {
        LOG_ERROR("Could not load window icon from {0}",spec.WindowIcon);
        return;
    }
    SDL_SetWindowIcon(NativeHandle, Icon);
    SDL_DestroySurface(Icon);
}
