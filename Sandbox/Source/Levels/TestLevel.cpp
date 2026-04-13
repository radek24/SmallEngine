//
// Created by radov on 18.03.2026.
//

#include "TestLevel.h"

#include <Engine/App.h>
#include <Engine/EventHandler.h>

#include "SecondLevel.h"
#include "Engine/Math/Rotator.h"

void TestLevel::OnEnter() {
    Level::OnEnter();
    /*
    Entity *e = Registry::CreateEntity("MojeEntita");
    Registry.FindEntity("MojeEntita");
    e.AddComponent<TransformComponent>(FVector(3,3,3));
    e.AddComponent<SpriteComponent>(FColor::White);
    e.AddComponent<Controller>(FColor::White);
    */
}

void TestLevel::OnUpdate(float DeltaTime) {
    Level::OnUpdate(DeltaTime);

}
void TestLevel::OnRender(const Renderer &Renderer) {
    Level::OnRender(Renderer);
    const Vector2f Pos(EventHandler::GetMousePos().X,EventHandler::GetMousePos().Y);
    Renderer.DrawDebugText(Pos,"Ahoj svete");
}

void TestLevel::OnExit() {
    Level::OnExit();
}
