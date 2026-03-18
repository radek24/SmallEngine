//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <memory>

#include "Renderer.h"
#include "Window.h"
#include "Core/Specifications.h"

/** Singleton class responsible for managing whole engine*/
class App {
public:
    explicit App(const Specifications &AppSpec);
    /** Start this engine with configuration passed in constructor*/
    void Run();
    /** Stops application, usually by users choice*/
    void Stop();
    /** Singleton instance getter*/
    [[nodiscard]] static App& Get();
    /** Time elapsed from application start*/
    [[nodiscard]] static float GetTime();
    /** Number of frames rendered since start  */
    [[nodiscard]] unsigned long long GetFrameCount() const{return FrameCounter;}

private:
    /** Current app specifications */
    Specifications AppSpecification;
    bool Running = false;
    unsigned long long FrameCounter;
    /** Prints current configuration into console*/
    void PrintInfo();

    std::unique_ptr<Window> AppWindow;
    std::unique_ptr<Renderer> AppRenderer;

};
