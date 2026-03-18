//
// Created by radov on 10.03.2026.
//


#pragma once
#include <unordered_set>
#include "Core/Window.h"
#include "Math/MathForward.h"

struct InputState
{
    /** Keys pressed by user this frame*/
    std::unordered_set<unsigned int> PressedKeys;
    /** Keys which is user holding currently*/
    std::unordered_set<unsigned int> HeldKeys;
    /** Keys released by user this frame*/
    std::unordered_set<unsigned int> ReleasedKeys;

    /** Mouse buttons pressed by user this frame*/
    std::unordered_set<unsigned int> PressedMouseButtons;
    /** Mouse buttons which is user holding currently*/
    std::unordered_set<unsigned int> HeldMouseButtons;
    /** Mouse buttons released by user this frame*/
    std::unordered_set<unsigned int> ReleasedMouseButtons;

    /** Current mouse position*/
    Vector2f MousePos;
    /** Difference from mouse position last frame*/
    Vector2f MouseDelta;
};

class EventHandler
{
public:
    /** Captures all inputs and populates InputState*/
    static void CaptureInput(SDL_Event Event);
    /** Gets current InputState*/
    [[nodiscard]] static InputState GetInputState();
    /** Call after frame finished, cleans up all the stale inputs */
    static void Cleanup();
    /** Polls input from app*/
    static void PollInputs();
    /** Gets set to true if we recieved a stop input (close window etc.)*/
    static bool ShouldStop();
};