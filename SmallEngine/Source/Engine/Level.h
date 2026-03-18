//
// Created by radov on 18.03.2026.
//

#pragma once
#include "Rendering/Renderer.h"

/** Base class for any level we want to display to the user, there can be only one level at a time. We don't support "layers" */
class SE_API Level {
public:
    Level() = default;
    virtual ~Level() = default;

    /** Called once when the level becomes active */
    virtual void OnEnter() {}

    /** Called every frame before rendering */
    virtual void OnUpdate(float DeltaTime) {}

    /** Called every frame to issue draw calls */
    virtual void OnRender(const Renderer& Renderer) {}

    /** Called once when the level is leaving */
    virtual void OnExit() {}
};