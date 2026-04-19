//
// Created by radov on 18.03.2026.
//

#include "TestLevel.h"

#include <ECS/Entity.h>
#include <ECS/Registry.h>
#include <Engine/App.h>
#include <Engine/EventHandler.h>

#include "ECS/Components/TransformComponent.h"
#include "ECS/Systems/MovementSystem.h"
#include "Engine/Math/Rotator.h"

void TestLevel::OnEnter() {
    Level::OnEnter();
    CurrentRegistry.AddSystem<MovementSystem>();
    Entity e = CurrentRegistry.CreateEntity();
    Transform t = { {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f} };
    CurrentRegistry.AddComponent<TransformComponent>(e,t);
}

void TestLevel::OnUpdate(float DeltaTime) {
    Level::OnUpdate(DeltaTime);
}
void TestLevel::OnRender(const Renderer &Renderer,float DeltaTime) {
    Level::OnRender(Renderer,DeltaTime);
    const Vector2f Pos(EventHandler::GetMousePos().X,EventHandler::GetMousePos().Y);
    Renderer.DrawDebugText(Pos,"Ahoj svete");
}

void TestLevel::OnExit() {
    Level::OnExit();
}
