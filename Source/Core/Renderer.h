//
// Created by radov on 09.03.2026.
//


#pragma once
#include <memory>

#include "Window.h"
#include "Math/Color.h"
#include "Math/MathForward.h"

class Renderer {
public:
    static std::unique_ptr<Renderer> Create(const Window& window);
    explicit Renderer(const Window& window);
    ~Renderer();
    /*Game loop functions*/
    /** Function responsible for clearing buffer and other starting operation*/
    void BeginFrame() const;
    /** Will present rendered image to screen*/
    void EndFrame() const;
    /** Clears screen with color*/
    void Clear() const;

    /*Rendering function*/
    void DrawRectangle(const Vector2f& Pos, const Vector2f &Size, const Color &ShapeColor) const;

private:
    SDL_Renderer* InternalRenderer;
};
