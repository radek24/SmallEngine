//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include "Specifications.h"


class Window {
    public:
    Window(const WindowSpecification& Specs);
    void Destroy();
    /** Update and clear window, poll events*/
    void Update();

    [[nodiscard]] bool ShouldClose() const;
    static int GetY();
    static int GetX();

};
