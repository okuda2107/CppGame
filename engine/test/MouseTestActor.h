#pragma once
#include "Actor.h"
#include "InputSystem.h"

class MouseTestActor : Actor {
   public:
    MouseTestActor(class Game* game) : Actor(game) {};
    void ActorInput(const InputState& state) override {
        // マウス
        const MouseState& mouse = state.Mouse;

        const Vector2& vec = mouse.GetPostion();

        if (mouse.GetButtonState(SDL_BUTTON_LEFT)) {
            std::cout << vec.x << ", " << vec.y << std::endl;
            std::cout << "Button left is down" << std::endl;
        }
        if (mouse.GetButtonState(SDL_BUTTON_RIGHT)) {
            std::cout << vec.x << ", " << vec.y << std::endl;
            std::cout << "Button right is down" << std::endl;
        }
        if (mouse.GetButtonState(SDL_BUTTON_MIDDLE)) {
            std::cout << vec.x << ", " << vec.y << std::endl;
            std::cout << "Button middle is down" << std::endl;
        }
        if (mouse.GetButtonState(SDL_BUTTON_X1)) {
            std::cout << vec.x << ", " << vec.y << std::endl;
            std::cout << "Button x1 is down" << std::endl;
        }
        if (mouse.GetButtonState(SDL_BUTTON_X2)) {
            std::cout << vec.x << ", " << vec.y << std::endl;
            std::cout << "Button x2 is down" << std::endl;
        }

        ButtonState buttonLeft = mouse.GetButtonState(SDL_BUTTON_LEFT);
        if (buttonLeft == EPressed)
            std::cout << "Button left is pressed" << std::endl;
        if (buttonLeft == EReleased)
            std::cout << "Button left is released" << std::endl;
        if (buttonLeft == EHeld)
            std::cout << "Button left is held" << std::endl;

        ButtonState buttonRight = mouse.GetButtonState(SDL_BUTTON_RIGHT);
        if (buttonRight == EPressed)
            std::cout << "Button right is pressed" << std::endl;
        if (buttonRight == EReleased)
            std::cout << "Button right is released" << std::endl;
        if (buttonRight == EHeld)
            std::cout << "Button right is held" << std::endl;

        ButtonState buttonMiddle = mouse.GetButtonState(SDL_BUTTON_MIDDLE);
        if (buttonMiddle == EPressed)
            std::cout << "Button middle is pressed" << std::endl;
        if (buttonMiddle == EReleased)
            std::cout << "Button middle is released" << std::endl;
        if (buttonMiddle == EHeld)
            std::cout << "Button middle is held" << std::endl;

        ButtonState buttonX1 = mouse.GetButtonState(SDL_BUTTON_X1);
        if (buttonX1 == EPressed)
            std::cout << "Button x1 is pressed" << std::endl;
        if (buttonX1 == EReleased)
            std::cout << "Button x1 is released" << std::endl;
        if (buttonX1 == EHeld) std::cout << "Button x1 is held" << std::endl;

        ButtonState buttonX2 = mouse.GetButtonState(SDL_BUTTON_X2);
        if (buttonX2 == EPressed)
            std::cout << "Button x2 is pressed" << std::endl;
        if (buttonX2 == EReleased)
            std::cout << "Button x2 is released" << std::endl;
        if (buttonX2 == EHeld) std::cout << "Button x2 is held" << std::endl;
    }
};
