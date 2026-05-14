//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <memory>
#include <SDL3/SDL.h>
#include "Engine/Specifications.h"

class SE_API Window {
public:
    /** Makes a unique pointer from this class */
    [[nodiscard]] static std::unique_ptr<Window> Create(const WindowSpecification& spec);
    /** Initializes from specifiactions*/
    explicit Window(const WindowSpecification& spec);
    ~Window();
    /** Poll every event for event handler*/
    void PollEvents(){};

    [[nodiscard]] uint32_t GetWidth()  const;
    [[nodiscard]] uint32_t GetHeight() const;
    /** Return native SDL handle*/
    [[nodiscard]] SDL_Window* GetNativeHandle() const;
    /** Returns this window own specifications*/
    [[nodiscard]] WindowSpecification GetSpecs();
private:
    SDL_Window* NativeHandle;
    WindowSpecification Specs;
    void SetupWindowIcon(const WindowSpecification& spec) const;

};
