#include <iostream>

#include "Log/Log.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    Log::Initialize();

    LOG_INFO("Test");
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_ERROR("SDL_Init failed: {}", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SmallEngine", 800, 600, 0);
    if (!window) {
        LOG_ERROR("SDL_CreateWindow failed: {}", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    LOG_INFO("SDL initialized successfully");

    SDL_Delay(10000);

    SDL_DestroyWindow(window);
    SDL_Quit();
}
