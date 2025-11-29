#pragma once

#include "UIScreen.h"

class HUD : public UIScreen {
   public:
    HUD(class Game* game);
    ~HUD() {};

    void Update(float deltaTime) {};
    void Draw(class Shader* shader) {};
    void ProcessInput(const class InputState& state) {};
    void HandleKeyPress(int key) {};
};
