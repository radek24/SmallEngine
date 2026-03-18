//
// Created by radov on 18.03.2026.
//

#include "TestLevel.h"

#include <Engine/EventHandler.h>

void TestLevel::OnEnter() {
    Level::OnEnter();
    LOG_INFO("Entered");
}

void TestLevel::OnUpdate(float DeltaTime) {
    Level::OnUpdate(DeltaTime);
}

void TestLevel::OnRender(const Renderer &Renderer) {
    Level::OnRender(Renderer);
    const Vector2f Pos(EventHandler::GetInputState().MousePos.X,EventHandler::GetInputState().MousePos.Y);
    const Vector2f Size(50,50);
    const Color Col(1,1,1);
    Renderer.DrawDebugText(Pos,"Ahoj svete");
   // Renderer.DrawRectangle(Pos,Size,Col);
}

void TestLevel::OnExit() {
    Level::OnExit();
}
