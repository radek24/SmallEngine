//
// Created by radov on 19.04.2026.
//

#include "RenderSystem.h"

#include <ECS/Registry.h>

#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"

void SE_API RenderSystem::Update(Registry& CurrentRegistry, float DeltaTime)
{
    struct DrawCall
    {
        SpriteComponent*    SC;
        TransformComponent* TC;
        int                 ZOrder;
    };
    std::vector<DrawCall> Queue;

    CurrentRegistry.MakeView<SpriteComponent, TransformComponent>().Each(
        [&](Entity E, SpriteComponent& SC, TransformComponent& TC)
    {
        if (!SC.Visible) return;
        Queue.push_back({ &SC, &TC, SC.ZOrder });
    });

    std::stable_sort(Queue.begin(), Queue.end(), [](const DrawCall& A, const DrawCall& B) {return A.ZOrder < B.ZOrder;});

    for (auto& [SC, TC, Z] : Queue)
    {
        auto TextureSize = Textures.GetSize(SC->Texture) * TC->Transform.Scale;
        Vector2f DrawPosition = Vector2f::ZeroVector;
        switch (SC->Positioning)
        {
            case Positioning::Center:
                DrawPosition = TC->Transform.Position - (TextureSize / 2.0f);
            break;
            case Positioning::LeftTop:
                DrawPosition = TC->Transform.Position;
            break;
            case Positioning::RightTop:
                DrawPosition = TC->Transform.Position - Vector2f(TextureSize.X, 0.0f);
            break;
            case Positioning::LeftCenter:
                DrawPosition = TC->Transform.Position - Vector2f(0.0f, TextureSize.Y / 2.0f);
            break;
            case Positioning::RightCenter:
                DrawPosition = TC->Transform.Position - Vector2f(TextureSize.X, TextureSize.Y / 2.0f);
            break;
            case Positioning::LeftBottom:
                DrawPosition = TC->Transform.Position - Vector2f(0.0f, TextureSize.Y);
            break;
            case Positioning::RightBottom:
                DrawPosition = TC->Transform.Position - Vector2f(TextureSize.X, TextureSize.Y);
            break;
            default:
                NoEntry();
        }

        RendererRef->DrawTexture(DrawPosition,TC->Transform.Rotation, TextureSize,Textures.Get(SC->Texture));
    }
}