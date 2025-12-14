#pragma once

namespace KeyboardAndMouse {
class InputSystem;
}

namespace OpenGL {
class Renderer;
}

namespace OpenAL {
class System;
}

class BonfireGame {
    class Game* mGame;
    class ActorsSystem* mActorsSystem;
    KeyboardAndMouse::InputSystem* mInputSystem;
    OpenGL::Renderer* mRenderer;
    OpenAL::System* mAudioSystem;

    class Vector2* mFieldMin;
    class Vector2* mFieldMax;

    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void LoadData();

   public:
    BonfireGame();

    bool Initialize();
    void RunLoop();
    void Shutdown();
};
