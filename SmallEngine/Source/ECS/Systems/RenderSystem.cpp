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
        auto TextureSize = Textures.GetSize(SC->Texture);
        RendererRef->DrawTexture(TC->Transform.Position,TC->Transform.Rotation,TC->Transform.Scale * TextureSize,Textures.Get(SC->Texture));
    }
}