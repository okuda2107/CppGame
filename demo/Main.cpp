#include "Game.h"
#include "temp.h"
#include "test/temp.h"

int main(int argc, char** argv) {
    hello();
    hello2();
    Game game;
    bool success = game.Initialize();
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
