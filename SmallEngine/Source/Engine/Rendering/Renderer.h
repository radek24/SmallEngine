//
// Created by radov on 09.03.2026.
//


#pragma once
#include <memory>

#include "Window.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/MathForward.h"
#include "Engine/Core.h"
#include "Engine/Math/Rotator.h"

class SE_API Renderer {
public:
    static std::unique_ptr<Renderer> Create(Window& window);
    explicit Renderer(Window& window);
    ~Renderer();
    /*Game loop functions*/
    /** Function responsible for clearing buffer and other starting operation*/
    void BeginFrame() const;
    /** Will present rendered image to screen*/
    void EndFrame() const;
    /** Clears screen with color specified*/
    void Clear() const;

    void SetClearColor(const Color& ClearColor);

    /** Loads texture from a path, do not use directly, prefer TextureManager*/
    [[nodiscard]] SDL_Texture* LoadTexture(const std::string& Path) const;

    void DrawRectangle(const Vector2f& Pos, const Vector2f& Size, const Color &ShapeColor= Color(1,1,1)) const;
    void DrawFilledCircle(const Vector2f& Pos,float Radius, const Color &PointColor= Color(1,1,1)) const;
    void DrawTexture(const Vector2f& Pos,const Rotator& Rot, const Vector2f& Size, SDL_Texture* Texture) const;
    void DrawTextureTinted(const Vector2f& Pos,const Rotator& Rot, const Vector2f& Size, SDL_Texture* Texture,const Color& Tint) const;
    void DrawDebugText(const Vector2f &Pos, const char *s, const Color &TextColor = Color(1,1,1)) const;
    void DrawLine(const Vector2f &StartPos,const Vector2f &EndPos,float Thickness = 1.0, const Color &LineColor = Color(1,1,1)  ) const;
    SDL_Texture* CreateTextureFromSurface(SDL_Surface* Surface);
private:
    SDL_Renderer* InternalRenderer;
    Color ClearColor = Color(0.1);
};
