//
// Created by radov on 18.03.2026.
//

#include "TestLevel.h"

#include <ECS/Entity.h>
#include <ECS/Registry.h>
#include <Engine/App.h>
#include <Engine/EventHandler.h>

#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/ScreenSpaceTextComponent.h"
#include "ECS/Components/SimpleKeyboardControllerComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/VelocityComponent.h"
#include "ECS/Systems/LifetimeSystem.h"
#include "ECS/Systems/MovementSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/SimpleControllerSystem.h"
#include "ECS/Systems/UIRenderSystem.h"
#include "Engine/Math/Rotator.h"

void TestLevel::OnEnter() {
    Level::OnEnter();
    //CurrentRegistry.AddSystem<MovementSystem>();
    CurrentRegistry.AddSystem<SimpleControllerSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(),*Textures);
    CurrentRegistry.AddSystem<LifetimeSystem>();
    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);

    Entity e = CurrentRegistry.CreateEntity();
    Transform t = { {0.0f, 0.0f}, {1.0f, 1.0f}, {0.0f} };
    SpriteComponent sc = {.Texture = Textures->LoadTexture("Resources/Textures/T_PlaceHolder.png")};
    VelocityComponent vc = {{10,0}};
    SimpleKeyboardControllerComponent skcc = {1000.0};
    LifetimeComponent ltc ={5.0f};
    ScreenSpaceTextComponent sstc = {"Ahoj","Resources/Fonts/PacFont.ttf",12};
    CurrentRegistry.AddComponent<TransformComponent>(e,t);
    CurrentRegistry.AddComponent<SimpleKeyboardControllerComponent>(e,skcc);
    //CurrentRegistry.AddComponent<SpriteComponent>(e,sc);
    CurrentRegistry.AddComponent<LifetimeComponent>(e,ltc);
    CurrentRegistry.AddComponent<ScreenSpaceTextComponent>(e,sstc);
    //CurrentRegistry.AddComponent<VelocityComponent>(e,vc);
}

void TestLevel::OnUpdate(float DeltaTime)
{
    Level::OnUpdate(DeltaTime);
}
void TestLevel::OnRender(const Renderer &Renderer,float DeltaTime)
{
    Level::OnRender(Renderer,DeltaTime);;
}

void TestLevel::OnExit()
{
    Level::OnExit();
}
