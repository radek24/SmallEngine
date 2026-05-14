//
// Created by radov on 03.05.2026.
//

#include "SimpleTestSaveLevel.h"

#include <Engine/EventHandler.h>

#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/TransformComponent.h"

void SimpleTestSaveLevel::OnEnter() {
    Level::OnEnter();
    for (int i = 0; i < 100; ++i)
    {
        auto e = CurrentRegistry.CreateEntity();
        CurrentRegistry.AddComponent<TransformComponent>(e, TransformComponent{{(float)i,1},{1,1},{1}});
        CurrentRegistry.AddComponent<RotatorComponent>(e,RotatorComponent{10});
    }
}

void SimpleTestSaveLevel::OnUpdate(float DeltaTime) {
    Level::OnUpdate(DeltaTime);
    if(EventHandler::IsKeyPressed(SDLK_X)) {
        CurrentRegistry.Save("Test.json");
    }
}

