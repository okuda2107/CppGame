#include "BonfireGame.h"
#include "Engine.h"
#include "game/object/ActorsSystem.h"
#include "input/InputSystem.h"
#include "renderer/Renderer.h"
#include "runtime/RuntimeSystem.h"

// ゲーム実装者がシステムの内容を定義
int main(int argc, char** argv) {
    ActorsSystem* actorsSystem = nullptr;
    BonfireGame* game = nullptr;
    Renderer* renderer = nullptr;
    InputSystem* inputSystem = nullptr;
    RuntimeSystem* runtimeSystem = nullptr;

    try {
        // game
        game = new BonfireGame();
        if (!game->Initialize())
            throw std::runtime_error("Failed to initialize game");

        // renderer
        renderer = new Renderer();
        if (!renderer->Initialize(1024.0f, 768.0f, "Chllut's Fire", false))
            throw std::runtime_error("Failed to initialize renderer");

        // input system
        inputSystem = new InputSystem();
        if (!inputSystem->Initialize())
            throw std::runtime_error("Failed to initialize input system");

        // runtime system
        runtimeSystem = new RuntimeSystem();
        if (!runtimeSystem->Initialize())
            throw std::runtime_error("Failed to initialize runtime system");

        // Load Scene

        Engine engine(game, inputSystem, renderer, runtimeSystem);

        engine.RunLoop();

    } catch (const std::runtime_error& e) {
        SDL_Log(e.what());
    }

    delete runtimeSystem;
    delete inputSystem;
    delete renderer;
    delete game;
    delete actorsSystem;

    return 0;
}
