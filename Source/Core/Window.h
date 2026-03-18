//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include "Specifications.h"


class Window {
public:
    [[nodiscard]] static std::unique_ptr<Window> Create(const WindowSpecification& spec);
    explicit Window(const WindowSpecification& spec);
    ~Window();
    void PollEvents(){};

    [[nodiscard]] uint32_t GetWidth()  const;
    [[nodiscard]] uint32_t GetHeight() const;
    [[nodiscard]] SDL_Window* GetNativeHandle() const;

    [[nodiscard]] bool ShouldClose() const {return false;};
private:
    SDL_Window* NativeHandle;

};
