#include "BonfireGame.h"

int main(int argc, char** argv) {
    // core
    GameCore* core = new GameCore();

    BonfireGame* game = new BonfireGame(core, actorsSystem);
    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
