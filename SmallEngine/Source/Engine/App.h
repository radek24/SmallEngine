//
// Created by Radovan Šťastný on 09.03.2026.
//

#pragma once
#include <memory>

#include "Level.h"
#include "Rendering/Renderer.h"
#include "Rendering/Window.h"
#include "Engine/Specifications.h"
#include "Engine/Core.h"

/** Singleton class responsible for managing whole engine*/
class SE_API App {
public:
    explicit App(const Specifications &AppSpec);


    virtual ~App();
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


    template<typename TLevel>
    /** Schedules level transition that will happen at the end of the frame so we can clean up everything safely. */
    void QueueLevelTransition()
    {
        LevelToTransitionTo = std::make_unique<TLevel>();
    }

    [[nodiscard]] Level* GetCurrentLevel() const;


private:
    /** Transition to level when possible (on the start of the frame)*/
    void TryToTransitionToLevel();
    /** Current app specifications */
    Specifications AppSpecification;
    bool Running = false;
    unsigned long long FrameCounter;
    /** Prints current configuration into console*/
    void PrintInfo();

    std::unique_ptr<Window> AppWindow;
    std::unique_ptr<Renderer> AppRenderer;
    std::unique_ptr<Level> LevelToTransitionTo;
    std::unique_ptr<Level> CurrentLevel;
};

/** Use this function to pass application as a client*/
App* CreateApplication();