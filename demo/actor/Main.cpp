#include "BonfireGame.h"

int main(int argc, char** argv) {
    BonfireGame game;
    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
