#pragma once
#include "ECS/System.h"
#include "Engine/Core.h"
#include "Engine/Rendering/Window.h"

class AsteroidsMovementSystem : public System
{
public:
    explicit AsteroidsMovementSystem(Window* Win, float MaxSpeed = 450.0f)
        : CurrentWindow(Win), MaxSpeed(MaxSpeed) {}

    void Update(Registry& CurrentRegistry, float DeltaTime) override;
    [[nodiscard]] SystemPhase GetPhase() const override { return SystemPhase::Update; }

private:
    Window* CurrentWindow;
    float MaxSpeed;
};