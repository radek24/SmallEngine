//
// Created by radov on 19.04.2026.
//

#include "RenderSystem.h"

#include <ECS/Registry.h>

#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"

RenderSystem::RenderSystem(Renderer *RendererRef, TextureManager &Textures) :RendererRef(RendererRef),Textures(Textures)
{
    //We expect to render a lot of entities
    Queue.reserve(1024);
}

void SE_API RenderSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    Queue.clear();

    CurrentRegistry.MakeView<SpriteComponent, TransformComponent>().Each(
        [&](Entity E, SpriteComponent& SC, TransformComponent& TC)
    {
        if (!SC.Visible) return;
        Queue.push_back({ &SC, &TC, SC.ZOrder,E.GetId()});
    });

    auto SortFunc = [](const DrawCall& A, const DrawCall& B)
    {
        if (A.ZOrder != B.ZOrder)
            return A.ZOrder < B.ZOrder;
        return A.EntityID < B.EntityID;
    };
    std::sort(Queue.begin(), Queue.end(), SortFunc);

    for (auto& [SC, TC, Z, E] : Queue)
    {
        auto TextureSize = Textures.GetSize(SC->Texture) * TC->Scale;
        Vector2f DrawPosition = Vector2f::ZeroVector;
        switch (SC->Positioning)
        {
            case Positioning::Center:
                DrawPosition = TC->Position - (TextureSize / 2.0f);
            break;
            case Positioning::LeftTop:
                DrawPosition = TC->Position;
            break;
            case Positioning::RightTop:
                DrawPosition = TC->Position - Vector2f(TextureSize.X, 0.0f);
            break;
            case Positioning::LeftCenter:
                DrawPosition = TC->Position - Vector2f(0.0f, TextureSize.Y / 2.0f);
            break;
            case Positioning::RightCenter:
                DrawPosition = TC->Position - Vector2f(TextureSize.X, TextureSize.Y / 2.0f);
            break;
            case Positioning::LeftBottom:
                DrawPosition = TC->Position - Vector2f(0.0f, TextureSize.Y);
            break;
            case Positioning::RightBottom:
                DrawPosition = TC->Position - Vector2f(TextureSize.X, TextureSize.Y);
            break;
            default:
                NoEntry();
        }

        RendererRef->DrawTextureTinted(DrawPosition,TC->Rotation, TextureSize,Textures.Get(SC->Texture), SC->Tint);
    }
}
