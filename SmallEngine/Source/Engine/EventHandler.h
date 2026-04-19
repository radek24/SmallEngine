//
// Created by radov on 10.03.2026.
//


#pragma once
#include <unordered_set>
#include "Engine/Rendering/Window.h"
#include "Math/MathForward.h"
#include "Engine/Core.h"

struct SE_API InputState
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
    /**Mouse buttons released by user this frame*/
    std::unordered_set<unsigned int> ReleasedMouseButtons;

    /** Current mouse position*/
    Vector2f MousePos;
    /** Difference from mouse position last frame*/
    Vector2f MouseDelta;
};

class SE_API EventHandler
{
public:
    /** Captures all inputs and populates InputState*/
    static void CaptureInput(SDL_Event Event);

    /** Returns if the key was pressed this frame*/
    [[nodiscard]] static bool IsKeyPressed(SDL_Keycode Key);
    /** Returns if the key is currently held */
    [[nodiscard]] static bool IsKeyHeld(SDL_Keycode Key);
    /** Returns if the key was released this frame */
    [[nodiscard]] static bool IsKeyReleased(SDL_Keycode Key);

    /** Returns if the mouse button was pressed this frame*/
    [[nodiscard]] static bool IsMouseButtonPressed(Uint16 Button);
    /** Returns if the mouse button is currently held */
    [[nodiscard]] static bool IsMouseButtonHeld(Uint16 Button);
    /** Returns if the key was released this frame */
    [[nodiscard]] static bool IsMouseButtonReleased(Uint16 Button);

    [[nodiscard]] static Vector2f GetMousePos();
    [[nodiscard]] static Vector2f GetMouseDelta();

    /** Gets current InputState*/
    [[nodiscard]] static InputState GetInputState();
    /** Call after frame finished, cleans up all the stale inputs */
    static void Cleanup();
    /** Polls input from app*/
    static void PollInputs();
    /** Gets set to true if we recieved a stop input (close window etc.)*/
    [[nodiscard]] static bool ShouldStop();
};

