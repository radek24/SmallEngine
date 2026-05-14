//
// Created by radov on 03.05.2026.
//

#include "SimpleTestSaveLevel.h"

#include <Engine/EventHandler.h>

#include "ECS/Components/TransformComponent.h"

void SimpleTestSaveLevel::OnEnter() {
    Level::OnEnter();
    auto e = CurrentRegistry.CreateEntity();
    CurrentRegistry.AddComponent<TransformComponent>(e, TransformComponent{{1,1},{1,1},{1}});


}

void SimpleTestSaveLevel::OnUpdate(float DeltaTime) {
    Level::OnUpdate(DeltaTime);
    if(EventHandler::IsKeyPressed(SDLK_X)) {
        CurrentRegistry.Save("Test.json");
    }
}

