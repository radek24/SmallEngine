//
// Created by radov on 18.03.2026.
//

#include "TestLevel.h"

#include <ECS/Entity.h>
#include <ECS/Registry.h>
#include <Engine/App.h>
#include <Engine/EventHandler.h>

#include "ECS/Components/LifetimeComponent.h"
#include "ECS/Components/UITextComponent.h"
#include "ECS/Components/SimpleKeyboardControllerComponent.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/RotatorComponent.h"
#include "ECS/Components/UIButtonComponent.h"
#include "ECS/Prefabs/Prefab.h"
#include "ECS/Systems/DebugDrawTransformSystem.h"
#include "ECS/Systems/LifetimeSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "ECS/Systems/RotatorSystem.h"
#include "ECS/Systems/SimpleControllerSystem.h"
#include "ECS/Systems/UIButtonSystem.h"
#include "ECS/Systems/UIRenderSystem.h"
#include "Engine/Math/Rotator.h"

void TestLevel::OnEnter() {
    Level::OnEnter();

    Prefab MyTestPrefab;
    MyTestPrefab
    .Add<TransformComponent>({{0.0f, 0.0f},{0.1f, 0.1f},{0.0f}})
    .Add<SpriteComponent>({.Texture = Textures->LoadTexture("Resources/Textures/T_PlaceHolder.png")});

    MyTestPrefab.Instantiate(CurrentRegistry);

    //CurrentRegistry.AddSystem<MovementSystem>();
    CurrentRegistry.AddSystem<SimpleControllerSystem>();
    CurrentRegistry.AddSystem<RotatorSystem>();
    CurrentRegistry.AddSystem<RenderSystem>(App::Get().GetRenderer(),*Textures);
    CurrentRegistry.AddSystem<LifetimeSystem>();
    CurrentRegistry.AddSystem<UIRenderSystem>(App::Get().GetRenderer(),*Fonts);
    CurrentRegistry.AddSystem<UIButtonSystem>();
/*
    Entity e = CurrentRegistry.CreateEntity();
    Entity button = CurrentRegistry.CreateEntity();
    Transform t = { {0.0f, 0.0f}, {0.1f, 0.1f}, {0.0f} };
    Transform bt = { {10.0f, 10.0f}, {1.0f, 1.0f}, {0.0f} };
    SpriteComponent sc = {.Texture = Textures->LoadTexture("Resources/Textures/T_PlaceHolder.png")};
    SimpleKeyboardControllerComponent skcc = {1000.0};
    LifetimeComponent ltc ={50.0f};
    UITextComponent sstc = {"Ahoj","Resources/Fonts/PacFont.ttf",20};
    auto OnHoverCall   = [this, button]{ CurrentRegistry.GetPool<UITextComponent>().Get(button).FontColor = Color(0.5f); };
    auto OnUnhoverCall = [this, button]{ CurrentRegistry.GetPool<UITextComponent>().Get(button).FontColor = Color(1.0f); };
    RotatorComponent rotator = {10.f};
    UIButtonComponent uibc = {.OnHover = OnHoverCall, .OnUnhover = OnUnhoverCall, .Size = {90,30}};

    CurrentRegistry.AddComponent<TransformComponent>(e,t);
    CurrentRegistry.AddComponent<SimpleKeyboardControllerComponent>(e,skcc);
    CurrentRegistry.AddComponent<SpriteComponent>(e,sc);
    CurrentRegistry.AddComponent<LifetimeComponent>(e,ltc);
    CurrentRegistry.AddComponent<RotatorComponent>(e,rotator);

    CurrentRegistry.AddComponent<UITextComponent>(button,sstc);
    CurrentRegistry.AddComponent<TransformComponent>(button,bt);
    CurrentRegistry.AddComponent<UIButtonComponent>(button,uibc);
    */
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
