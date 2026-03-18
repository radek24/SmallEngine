//
// Created by radov on 09.03.2026.
//


#pragma once
#include <memory>

#include "Window.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/MathForward.h"
#include "Engine/Core.h"

class SE_API Renderer {
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

    void SetClearColor(const Color& ClearColor);

    void DrawRectangle(const Vector2f& Pos, const Vector2f& Size, const Color &ShapeColor) const;
    void DrawPoint(const Vector2f& Pos,float Radius, const Color &PointColor) const;
    void DrawDebugText(const Vector2f &Pos, const char *s, const Color &TextColor = Color(1,1,1)) const;

private:
    SDL_Renderer* InternalRenderer;
    Color ClearColor = Color(0.1);
};
