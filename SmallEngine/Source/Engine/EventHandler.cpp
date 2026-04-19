//
// Created by radov on 10.03.2026.
//

#include "EventHandler.h"

static InputState CurrentInputState;
static Vector2f LastCursorPos = Vector2f(0,0);
static bool Stop = false;

void EventHandler::CaptureInput(SDL_Event Event)
{
    if(Event.type == SDL_EVENT_KEY_DOWN)
    {
        CurrentInputState.PressedKeys.insert(Event.key.key);
        CurrentInputState.HeldKeys.insert(Event.key.key);
    }
    if(Event.type == SDL_EVENT_KEY_UP)
    {
        CurrentInputState.HeldKeys.erase(Event.key.key);
        CurrentInputState.ReleasedKeys.insert(Event.key.key);
    }
    if(Event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        CurrentInputState.PressedMouseButtons.insert(Event.button.button);
        CurrentInputState.HeldMouseButtons.insert(Event.button.button);
    }
    if(Event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        CurrentInputState.HeldMouseButtons.erase(Event.button.button);
        CurrentInputState.ReleasedMouseButtons.insert(Event.button.button);
    }
    if(Event.type == SDL_EVENT_MOUSE_MOTION)
    {
        CurrentInputState.MouseDelta = Vector2f(LastCursorPos - Vector2f(Event.button.x,Event.button.y));
        CurrentInputState.MousePos = Vector2f(Event.button.x,Event.button.y);
        LastCursorPos = Vector2f(Event.button.x,Event.button.y);
    }
}

bool EventHandler::IsKeyPressed(SDL_Keycode Key)
{
    return GetInputState().PressedKeys.contains(Key);
}

bool EventHandler::IsKeyHeld(SDL_Keycode Key)
{
    return GetInputState().HeldKeys.contains(Key);
}

bool EventHandler::IsKeyReleased(SDL_Keycode Key)
{
    return GetInputState().ReleasedKeys.contains(Key);
}

bool EventHandler::IsMouseButtonPressed(Uint16 Button)
{
    return GetInputState().PressedMouseButtons.contains(Button);
}

bool EventHandler::IsMouseButtonHeld(Uint16 Button)
{
    return GetInputState().HeldMouseButtons.contains(Button);
}

bool EventHandler::IsMouseButtonReleased(Uint16 Button)
{
    return GetInputState().ReleasedMouseButtons.contains(Button);
}

InputState EventHandler::GetInputState()
{
    return CurrentInputState;
}

Vector2f EventHandler::GetMousePos()
{
    return CurrentInputState.MousePos;
}
Vector2f EventHandler::GetMouseDelta()
{
    return CurrentInputState.MouseDelta;
}


void EventHandler::Cleanup()
{
    CurrentInputState.PressedKeys.clear();
    CurrentInputState.ReleasedKeys.clear();

    CurrentInputState.PressedMouseButtons.clear();
    CurrentInputState.ReleasedMouseButtons.clear();

    CurrentInputState.MouseDelta = Vector2f(0);
}

void EventHandler::PollInputs()
{
    Stop = false;
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT) Stop = true;
        CaptureInput(e);
    }

}

bool EventHandler::ShouldStop()
{
    return Stop;
}
